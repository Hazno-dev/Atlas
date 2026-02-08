// Hazno - 2026

// ReSharper disable CppWrongIncludesOrder
module;

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#include <Windows.h> //DO NOT CHANGE THE INCLUDE ORDER. #include <Windows.h> MUST COME FIRST
#include <Winternl.h>
#include <TlHelp32.h>

#include "Common/Private/Common.Macros.h"
#include "Private/Platform.Windows.h"

#undef LoadLibrary
#undef GetModuleHandle
#undef GetModuleHandleEx
#undef GetModuleFileName

module Atlas.Platform;
import std;

namespace
{
	int __stdcall VectoredExceptionHandler(EXCEPTION_POINTERS* exception)
	{
		if (exception->ExceptionRecord->ExceptionCode == static_cast<uint32>(WIN_EXCEPTION_CODE::BREAKPOINT) ||
			exception->ExceptionRecord->ExceptionCode == static_cast<uint32>(WIN_EXCEPTION_CODE::SINGLE_STEP) ||
			exception->ExceptionRecord->ExceptionCode == static_cast<uint32>(WIN_EXCEPTION_CODE::GUARD_PAGE) ||
			exception->ExceptionRecord->ExceptionCode == static_cast<uint32>(WIN_EXCEPTION_CODE::MSVC_RAISED))
			return SYS_EXCEPTION_CONTINUE_SEARCH;
		if (exception->ExceptionRecord->ExceptionCode == static_cast<uint32>(WIN_EXCEPTION_CODE::ACCESS_VIOLATION)) {
			if (exception->ContextRecord->Rip > Atlas::Platform::GetBadReadPtr() && exception->ContextRecord->Rip -
				Atlas::Platform::GetBadReadPtr() < 0x100)
				return SYS_EXCEPTION_CONTINUE_SEARCH;
		}
		if (exception->ExceptionRecord->ExceptionCode == 0x40010006)
			return SYS_EXCEPTION_CONTINUE_SEARCH;
		if (exception->ExceptionRecord->ExceptionCode == 0xc0000008)
			return SYS_EXCEPTION_CONTINUE_EXECUTION;

		//LOG_CORE_e(exception);
		return SYS_EXCEPTION_CONTINUE_SEARCH;
	}
}

namespace Atlas::Platform
{
	PVECTORED_EXCEPTION_HANDLER GetExceptionHandler()
	{
		return reinterpret_cast<PVECTORED_EXCEPTION_HANDLER>(VectoredExceptionHandler);
	}

	int64 GetBadReadPtr()
	{
		return reinterpret_cast<uint64>(std::addressof(IsBadReadPtr));
	}

	ATLAS_NODISCARD uint32 GetPageSize()
	{
		SYSTEM_INFO sys_info;
		GetSystemInfo(&sys_info);
		return sys_info.dwPageSize;
	}

	ATLAS_NODISCARD void* GetCurrentProcessHandle()
	{
		return GetCurrentProcess();
	}

	ATLAS_NODISCARD uint32 GetCurrentProcessId()
	{
		return ::GetCurrentProcessId();
	}

	ATLAS_NODISCARD void* GetCurrentThreadHandle()
	{
		return GetCurrentThread();
	}

	ATLAS_NODISCARD uint32 GetCurrentThreadId()
	{
		return ::GetCurrentThreadId();
	}

	bool CloseHandle(void* handle)
	{
		return ::CloseHandle(handle) != 0;
	}

	ATLAS_NODISCARD void* CreateToolhelp32Snapshot(const uint32 dwFlags, const uint32 th32_process_id)
	{
		return ::CreateToolhelp32Snapshot(dwFlags, th32_process_id);
	}

	HMODULE GetModuleHandleAImpl(const char* lpModuleName)
	{
		return GetModuleHandleA(lpModuleName);
	}

	HMODULE GetModuleHandleWImpl(const wchar_t* lpModuleName)
	{
		return GetModuleHandleW(lpModuleName);
	}

	bool GetModuleHandleExAImpl(uint32 flags, const char* lpModuleName, HMODULE* phModule)
	{
		return GetModuleHandleExA(flags, lpModuleName, phModule) != 0;
	}
	bool GetModuleHandleExWImpl(uint32 flags, const wchar_t* lpModuleName, HMODULE* phModule)
	{
		return GetModuleHandleExW(flags, lpModuleName, phModule) != 0;
	}

	uint32 GetModuleFileNameAImpl(HMODULE hModule, char* lpModuleName, uint32 nSize)
	{
		return GetModuleFileNameA(hModule, lpModuleName, nSize);
	}

	uint32 GetModuleFileNameWImpl(HMODULE hModule, wchar_t* lpModuleName, uint32 nSize)
	{
		return GetModuleFileNameW(hModule, lpModuleName, nSize);
	}

	HMODULE LoadLibraryAImpl(const char* lpLibFileName)
	{
		return LoadLibraryA(lpLibFileName);
	}

	HMODULE LoadLibraryWImpl(const wchar_t* lpLibFileName)
	{
		return LoadLibraryW(lpLibFileName);
	}

	ATLAS_NODISCARD uint32 Stacktrace(void** stack, const uint32 size, const uint32 skip_frames)
	{
		return RtlCaptureStackBackTrace(skip_frames, size, stack, nullptr);
	}

	bool Module32FirstImpl(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
	{
		return Module32First(hSnapshot, lpme) != 0;
	}

	bool Module32NextImpl(HANDLE hSnapshot, LPMODULEENTRY32 lpme)
	{
		return Module32Next(hSnapshot, lpme) != 0;
	}

	bool DisableThreadLibraryCallsImpl(HMODULE hLibModule)
	{
		return DisableThreadLibraryCalls(hLibModule);
	}

	bool FreeLibraryImpl(HMODULE hLibModule)
	{
		return FreeLibrary(hLibModule) != 0;
	}

	FARPROC GetProcAddressImpl(HMODULE hModule, LPCSTR lpProcName)
	{
		return GetProcAddress(hModule, lpProcName);
	}
}
