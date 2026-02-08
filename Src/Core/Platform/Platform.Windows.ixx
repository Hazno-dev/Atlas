// Hazno - 2026

export module Atlas.Platform;
export import :Types;
export import :Extension;
import Atlas.Common;
import std;

namespace Atlas::Platform
{
	ATLAS_NODISCARD HMODULE GetModuleHandleAImpl(const char* lpModuleName);
	ATLAS_NODISCARD HMODULE GetModuleHandleWImpl(const wchar_t* lpModuleName);

	ATLAS_NODISCARD bool GetModuleHandleExAImpl(uint32 flags, const char* lpModuleName, HMODULE* phModule);
	ATLAS_NODISCARD bool GetModuleHandleExWImpl(uint32 flags, const wchar_t* lpModuleName, HMODULE* phModule);

	ATLAS_NODISCARD uint32 GetModuleFileNameAImpl(HMODULE hModule, char* lpModuleName, uint32 nSize);
	ATLAS_NODISCARD uint32 GetModuleFileNameWImpl(HMODULE hModule, wchar_t* lpModuleName, uint32 nSize);

	ATLAS_NODISCARD HMODULE LoadLibraryAImpl(const char* lpLibFileName);
	ATLAS_NODISCARD HMODULE LoadLibraryWImpl(const wchar_t* lpLibFileName);

	ATLAS_NODISCARD uint32 Stacktrace(void** stack, uint32 size, uint32 skip_frames = 2);

	bool Module32FirstImpl(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
	bool Module32NextImpl(HANDLE hSnapshot, LPMODULEENTRY32 lpme);
	bool DisableThreadLibraryCallsImpl(HMODULE hLibModule);
	bool FreeLibraryImpl(HMODULE hLibModule);
	FARPROC GetProcAddressImpl(HMODULE hModule, LPCSTR lpProcName);
}

export namespace Atlas::Platform
{
	PVECTORED_EXCEPTION_HANDLER GetExceptionHandler();

	ATLAS_NODISCARD int64 GetBadReadPtr();

	ATLAS_NODISCARD uint32 GetPageSize();

	ATLAS_NODISCARD void* GetCurrentProcessHandle();

	ATLAS_NODISCARD uint32 GetCurrentProcessId();

	ATLAS_NODISCARD void* GetCurrentThreadHandle();

	ATLAS_NODISCARD uint32 GetCurrentThreadId();

	bool CloseHandle(void* handle);

	template <Cpt_C_W_Str t_str>
	ATLAS_NODISCARD HMODULE constexpr GetModuleHandle(t_str lpModuleName)
	{
		if constexpr (std::is_same_v<t_str, const char*>) {
			return GetModuleHandleAImpl(lpModuleName);
		} else {
			return GetModuleHandleWImpl(lpModuleName);
		}
	}

	template <Cpt_C_W_Str t_str>
	ATLAS_NODISCARD bool constexpr GetModuleHandleEx(uint32 flags, t_str lpModuleName, HMODULE* phModule)
	{
		if constexpr (std::is_same_v<t_str, const char*>) {
			return GetModuleHandleExAImpl(flags, lpModuleName, phModule);
		} else {
			return GetModuleHandleExWImpl(flags, lpModuleName, phModule);
		}
	}

	template <Cpt_Ptr t_module, Cpt_C_W_Str t_str>
	ATLAS_NODISCARD uint32 constexpr GetModuleFileName(t_module hModule, t_str lpModuleName, uint32 nSize)
	{
		if constexpr (std::is_same_v<t_str, const char*>) {
			return GetModuleFileNameAImpl(hModule, lpModuleName, nSize);
		} else {
			return GetModuleFileNameWImpl(hModule, lpModuleName, nSize);
		}
	}

	template <Cpt_C_W_Str t_str>
	ATLAS_NODISCARD HMODULE constexpr LoadLibrary(t_str lpLibFileName)
	{
		if constexpr (std::is_same_v<t_str, const char*>) {
			return LoadLibraryAImpl(lpLibFileName);
		} else {
			return LoadLibraryWImpl(lpLibFileName);
		}
	}

	template <uint32 t_size>
	ATLAS_NODISCARD constexpr std::span<void* const> Stacktrace(const uint32 skip_frames = 2)
	{
		static_assert(t_size <= 128, "Stacktrace size too large");

		thread_local void* stack[t_size];
		const auto captured = Stacktrace(stack, t_size, skip_frames);
		return std::span<void* const>(stack, captured);
	}

	ATLAS_NODISCARD void* CreateToolhelp32Snapshot(uint32 dwFlags, uint32 th32_process_id);

	template <Cpt_Ptr t_snap, Cpt_Ptr t_entry>
	bool Module32First(t_snap hSnapshot, t_entry entry)
	{
		return Module32FirstImpl(hSnapshot, entry) != 0;
	}

	template <Cpt_Ptr t_snap, Cpt_Ptr t_entry>
	bool Module32Next(t_snap hSnapshot, t_entry entry)
	{
		return Module32NextImpl(hSnapshot, entry) != 0;
	}

	template <Cpt_Ptr t_input>
	bool DisableThreadLibraryCalls(t_input hLibModule)
	{
		return DisableThreadLibraryCallsImpl(hLibModule);
	}

	template <Cpt_Ptr t_input>
	bool FreeLibrary(t_input hLibModule)
	{
		return FreeLibraryImpl(hLibModule) != 0;
	}

	template <Cpt_Ptr t_input>
	FARPROC GetProcAddress(t_input hModule, const char* lpProcName)
	{
		return GetProcAddressImpl(hModule, lpProcName);
	}
}
