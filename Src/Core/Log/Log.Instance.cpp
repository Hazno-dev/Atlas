// Hazno - 2026

module;

#define SPDLOG_FMT_EXTERNAL 1
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/dist_sink.h>
#include <filesystem>

module Atlas.Log;
import Atlas.Platform;
import Atlas.Process;
import fmt;

namespace Atlas::Logs
{
	LogInstance::LogInstance(const std::string& name, const std::string& path) :
		m_name(std::move(name)),
		m_sink(std::make_shared<spdlog::sinks::dist_sink_mt>()),
		Default(std::make_shared<spdlog::logger>(m_name, m_sink)),
		Nested(std::make_unique<spdlog::logger>(m_name + "_NESTED", m_sink)),
		Clean(std::make_unique<spdlog::logger>(m_name + "_CLEAN", m_sink))
	{
		const auto target_path = std::filesystem::path(path);
		const auto log_path = target_path.parent_path().string();
		const auto file_name = target_path.filename().string();
		const auto ext = target_path.extension().string();

		const auto latest = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path + file_name + ext, true);
		const auto time_stamp = std::make_shared<spdlog::sinks::basic_file_sink_mt>(log_path + file_name + "_"
			+ std::to_string(std::chrono::system_clock::now().time_since_epoch().count()) + ext);

		auto cur_sink = reinterpret_cast<spdlog::sinks::dist_sink_mt*>(latest.get());
		cur_sink->add_sink(latest);
		cur_sink->add_sink(time_stamp);

#if _DEBUG
		auto patterner = std::make_unique<logger_patterner>("[%T:%e] [%L] %-16!s%4# << %v");
		patterner->pattern_logger(Nested, "[%T:%e] [%L] %-14!s%4# << -  %v");
		patterner->pattern_logger(Clean, "%v");
#else
		auto patterner = std::make_unique<Logger_Patterner>("[%T:%e] [%L] %-10!s << %v");
		patterner->PatternLogger(Nested, "[%T:%e] [%L]         << -  %v");
		patterner->PatternLogger(Clean, "%v");
#endif

		cur_sink->set_formatter(std::move(patterner));

		Clean->info("====================================================================");
		Clean->info("-   ");
		Clean->info("-   {} Log Initialized 💅 - v{} ({} Build)", name, VERSION_STRING, BUILD_TYPE);
		Clean->info("-   ");
		Clean->info("====================================================================");
		Clean->info("-   ");
		Clean->info("-   Process Base: {:n} {:n}", FMT_ADDR(Process::GetProcessModule().Base()), FMT_ADDR(Process::GetProcessModule().Base()));
		Clean->info("-   Self Base:    {:n} {:n}", FMT_ADDR(Process::GetSelfModule().Base()), FMT_ADDR(Process::GetSelfModule().Size()));
		Clean->info("-   Main Thread:  {}", Platform::GetCurrentThreadId());
		Clean->info("-   ");
		Clean->info("====================================================================");
		Clean->info(" ");
	}

	void LogInstance::Flush() const
	{
		if (!Default) {
			return;
		}

		Default->flush();
		Nested->flush();
		Clean->flush();
	}

	void LogInstance::LogException(const _EXCEPTION_RECORD* record) const
	{
		Nested->critical("Win32 Exception raised at {}", FMT_ADDR(record->ExceptionAddress));

		Newline();
		Nested->critical("***  General Information");
		Nested->critical("Desc:   \"{}\"", Platform::ErrorToString(record));
		Nested->critical("Thread: {0:n}     Flags:  {1:08b} ({1:0>4})", FMT_ADDR(Platform::GetCurrentThreadId()), record->ExceptionFlags);
		Nested->critical("Code:   {:n}     Params: {}", FMT_ADDR(record->ExceptionCode), record->NumberParameters);
		for (int i = 0; i < record->NumberParameters; i++) {
			Nested->critical("Param   {0:0>2}: {1:nv}", i, FMT_ADDR(record->ExceptionInformation[i]));
		}

		if (record->ExceptionCode == WIN_EXCEPTION_CODE::UNCAUGHT_CXX_EXCEPTION && record->NumberParameters >= 3) {
			Newline();
			Nested->critical("***  C++ Exception");
			if (const auto whatStr = Platform::ErrorToString(record->ExceptionInformation[1])) {
				Nested->critical("std::exception::what(): \"{}\"", whatStr);
			} else {
				Nested->critical("Failed to cast to std::exception!");
			}
		}

		if (record->ExceptionRecord) {
			Newline();
			Nested->critical("***  Chained Exception");
			LogException(record->ExceptionRecord);
		}
	}

	void LogInstance::LogException(const _CONTEXT* ctx) const
	{
		Newline();
		Nested->critical("***  Registers");
		Nested->critical("DR0: {:n}     DR3: {:n}", FMT_ADDR(ctx->Dr0), FMT_ADDR(ctx->Dr3));
		Nested->critical("DR1: {:n}     DR6: {:n}", FMT_ADDR(ctx->Dr1), FMT_ADDR(ctx->Dr6));
		Nested->critical("DR2: {:n}     DR7: {:n}", FMT_ADDR(ctx->Dr2), FMT_ADDR(ctx->Dr7));
		Nested->critical("RAX: {:n}     RBP: {:n}     R10: {:n}", FMT_ADDR(ctx->Rax), FMT_ADDR(ctx->Rbp), FMT_ADDR(ctx->R10));
		Nested->critical("RCX: {:n}     RSI: {:n}     R11: {:n}", FMT_ADDR(ctx->Rcx), FMT_ADDR(ctx->Rsi), FMT_ADDR(ctx->R11));
		Nested->critical("RDX: {:n}     RDI: {:n}     R12: {:n}", FMT_ADDR(ctx->Rdx), FMT_ADDR(ctx->Rdi), FMT_ADDR(ctx->R12));
		Nested->critical("RBX: {:n}      R8: {:n}     R13: {:n}", FMT_ADDR(ctx->Rbx), FMT_ADDR(ctx->R8), FMT_ADDR(ctx->R13));
		Nested->critical("RSP: {:n}      R9: {:n}     R14: {:n}", FMT_ADDR(ctx->Rsp), FMT_ADDR(ctx->R9), FMT_ADDR(ctx->R14));
		Nested->critical("R15: {:n}     RIP: {:n}", FMT_ADDR(ctx->R15), FMT_ADDR(ctx->Rip));
	}

	void LogInstance::LogException(const _EXCEPTION_POINTERS* ex) const
	{
		LogException(ex->ExceptionRecord);
		LogException(ex->ContextRecord);
	}

	void LogInstance::LogCallstack(const LogLevel level) const
	{
		thread_local void* stack[48];

		Newline();
		Nested->critical("***  Callstack");
		const auto lvl = static_cast<spdlog::level::level_enum>(level);
		const auto traces = Platform::Stacktrace<48>();

		auto i = 0;
		for (auto trace : traces) {
			Nested->log(lvl, "Address {:0>2}: {}", i++, FMT_ADDR(trace));
		}

		Flush();
	}

	void LogInstance::Newline() const
	{
		Clean->info(" ");
	}
}
