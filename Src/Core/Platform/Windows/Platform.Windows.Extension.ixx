// Hazno - 2026

module;

#include "string.h"

export module Atlas.Platform:Extension;
import :Types;
import Atlas.Common;

export namespace Atlas::Platform
{
	template <typename t_type>
	ATLAS_NODISCARD constexpr const char* ErrorToString(t_type exception)
	{
		static_assert(sizeof(t_type) == 0, "Unsupported type for ErrorToString");
		return "UNSUPPORTED TYPE";
	}

	template <>
	ATLAS_NODISCARD inline const char* ErrorToString(const WIN_EXCEPTION_CODE exception)
	{
		switch (exception) {
			case WIN_EXCEPTION_CODE::ACCESS_VIOLATION:
				return "Access violation. Tried to read or write to a virtual address without access.";
			case WIN_EXCEPTION_CODE::ARRAY_BOUNDS_EXCEEDED:
				return "Array access out of bounds.";
			case WIN_EXCEPTION_CODE::BREAKPOINT:
				return "Breakpoint reached.";
			case WIN_EXCEPTION_CODE::DATATYPE_MISALIGNMENT:
				return "Tried to read or write data that is misaligned on hardware that does not provide alignment.";
			case WIN_EXCEPTION_CODE::FLT_DENORMAL_OPERAND:
				return "Floating point operand is denormal.";
			case WIN_EXCEPTION_CODE::FLT_DIVIDE_BY_ZERO:
				return "Floating point division by zero.";
			case WIN_EXCEPTION_CODE::FLT_INEXACT_RESULT:
				return "Floating point inaccurate result.";
			case WIN_EXCEPTION_CODE::FLT_INVALID_OPERATION:
				return "Floating point invalid operation.";
			case WIN_EXCEPTION_CODE::FLT_OVERFLOW:
				return "Floating point overflow. Exponent is greater than the magnitude allowed by the corresponding type.";
			case WIN_EXCEPTION_CODE::FLT_STACK_CHECK:
				return "Floating point operation caused a stack overflow/underflow";
			case WIN_EXCEPTION_CODE::FLT_UNDERFLOW:
				return "Floating point underflow. Exponent is less than the magnitude allowed by the corresponding type.";
			case WIN_EXCEPTION_CODE::ILLEGAL_INSTRUCTION:
				return "Attempted to execute an illegal instruction.";
			case WIN_EXCEPTION_CODE::IN_PAGE_ERROR:
				return "Tried to access a page that was not present, and the system was unable to load the page.";
			case WIN_EXCEPTION_CODE::INT_DIVIDE_BY_ZERO:
				return "Int divided by zero.";
			case WIN_EXCEPTION_CODE::INT_OVERFLOW:
				return "Int overflow.";
			case WIN_EXCEPTION_CODE::INVALID_DISPOSITION:
				return "Exception handler sent an invalid disposition to the exception dispatcher.";
			case WIN_EXCEPTION_CODE::INVALID_HANDLE:
				return "Invalid handle.";
			case WIN_EXCEPTION_CODE::NONCONTINUABLE_EXCEPTION:
				return "Tried to continue execution after a noncontinuable exception occurred.";
			case WIN_EXCEPTION_CODE::PRIVILEGED_INSTRUCTION:
				return "Tried to execute an instruction whose operation is not allowed in the current machine mode.";
			case WIN_EXCEPTION_CODE::GUARD_PAGE:
				return "Attempted guard page access.";
			case WIN_EXCEPTION_CODE::SINGLE_STEP:
				return "Single debug step. One instruction has been executed.";
			case WIN_EXCEPTION_CODE::STACK_OVERFLOW:
				return "Stack overflow.";
			case WIN_EXCEPTION_CODE::MSVC_RAISED:
				return "Caller raised to set a thread name on the Visual Studio debugger.";
			case WIN_EXCEPTION_CODE::UNCAUGHT_CXX_EXCEPTION:
				return "Uncaught C++ EH exception.";
			default:
				return "Unknown exception code.";
		}
	}

	template <>
	ATLAS_NODISCARD inline const char* ErrorToString(const EXCEPTION_RECORD* exception)
	{
		return ErrorToString(static_cast<WIN_EXCEPTION_CODE>(exception->ExceptionCode));
	}

	template <>
	ATLAS_NODISCARD inline const char* ErrorToString(const uint64 exception)
	{
		thread_local char buffer[1024];
		__try {
			auto* e = reinterpret_cast<const std::exception*>(exception);
			if (!e) {
				return nullptr;
			}

			const char* p = e->what();
			if (!p) {
				return nullptr;
			}

			strncpy_s(buffer, p, sizeof(buffer) - 1);
			buffer[sizeof(buffer) - 1] = '\0';
			return _strdup(buffer);
		} __except (SYS_EXCEPTION_EXECUTE_HANDLER) {
			return nullptr;
		}
	}
}
