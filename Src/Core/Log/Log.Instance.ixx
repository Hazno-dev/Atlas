// Hazno - 2026

module;

#define SPDLOG_SHORT_LEVEL_NAMES { "TRC", "DBG", "INF", "WRN", "ERR", "!!!", "OFF" }

#define SPDLOG_FMT_EXTERNAL 1
#include <spdlog/spdlog.h>

export module Atlas.Log:Instance;

export namespace Atlas::Logs
{
	enum LogLevel : int
	{
		Trace    = SPDLOG_LEVEL_TRACE,
		Debug    = SPDLOG_LEVEL_DEBUG,
		Info     = SPDLOG_LEVEL_INFO,
		Warn     = SPDLOG_LEVEL_WARN,
		Error    = SPDLOG_LEVEL_ERROR,
		Critical = SPDLOG_LEVEL_CRITICAL,
	};

	class LogInstance
	{
		const std::string m_name;
		const std::shared_ptr<spdlog::sinks::sink> m_sink;

		public:
			// Logger with default formatting.
			const std::shared_ptr<spdlog::logger> Default;

			// Logger with nested formatting. Useful for array/table-like logs, and for callstacks.
			const std::shared_ptr<spdlog::logger> Nested;

			// Logger without any preformatted information. Use sparingly!
			const std::shared_ptr<spdlog::logger> Clean;

			LogInstance(const std::string& name, const std::string& path);

			void Flush() const;

			void LogException(const _EXCEPTION_RECORD* record) const;
			void LogException(const _CONTEXT* ctx) const;
			void LogException(const _EXCEPTION_POINTERS* ex) const;
			void LogCallstack(LogLevel level) const;

			void Newline() const;
	};
}
