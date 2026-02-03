// Hazno - 2026

module;

module Atlas.Process;
import Atlas.Common;
import Atlas.Common.Platform;
import std.compat;

using LdrRegisterDllNotification_t   = NTSTATUS(ATLAS_STDCALL*)(uint32 Flags, PVOID NotificationFunction, PVOID Context, PVOID* Cookie);
using LdrUnregisterDllNotification_t = NTSTATUS(ATLAS_STDCALL*)(PVOID Cookie);

namespace Atlas::Process
{
	inline std::vector<Module> s_modules{};

	inline std::atomic s_dirty{true};
	inline PVOID s_cookie = nullptr;

	inline std::optional<Module> s_programBounds{};
	inline std::optional<Module> s_runtimeBounds{};

	uint64 Module::RVA(const uint64 absolute) const
	{
		if (absolute < m_base || absolute >= m_end) {
			return 0;
		}

		return absolute - m_base;
	}

	uint64 Module::VA(const uint64 relative) const
	{
		const auto res = m_base + relative;
		if (res < m_base || res >= m_end) {
			return 0;
		}

		return res;
	}

	static void ATLAS_STDCALL DllNotify(uint32 reason, const void* data, void* ctx)
	{
		s_dirty.store(true, std::memory_order_relaxed);
	}

	void TryUpdateModules()
	{
		if (!s_dirty.exchange(false, std::memory_order_relaxed)) {
			return;
		}

		s_modules.clear();

		const uint32 pid = GetCurrentProcessId();
		const auto snap  = CreateToolhelp32Snapshot(TH32_SNAP_MODULE | TH32_SNAP_MODULE32, pid);
		if (snap == SYS_INVALID_HANDLE_VALUE) {
			printf("Invalid handle returned from snapshot in TryUpdateModules\n");
			return;
		}

		MODULEENTRY32 me{};
		me.dwSize = sizeof(me);

		if (!Module32First(snap, &me)) {
			CloseHandle(snap);
			printf("Failed to get first module in TryUpdateModules\n");
			return;
		}

		auto mod = Module(reinterpret_cast<uint64>(me.modBaseAddr),
		                  reinterpret_cast<uint64>(me.modBaseAddr + me.modBaseSize),
		                  me.modBaseSize,
		                  me.szModule);
		do {
			s_modules.emplace_back(mod);
		}
		while (Module32Next(snap, &me));

		CloseHandle(snap);
		std::ranges::sort(s_modules, [] (const Module& a, const Module& b) {
			return a.Base() < b.Base();
		});

		s_programBounds.emplace(*GetModuleForAddress(GetModuleHandle(nullptr)));
		s_runtimeBounds.emplace(*GetModuleForAddress(reinterpret_cast<uint64>(&Initialize)));
	}

	const Module& GetProcessModule()
	{
		return *s_programBounds;
	}

	const Module& GetSelfModule()
	{
		return *s_runtimeBounds;
	}

	const Module* GetModuleForAddress(uint64 addr)
	{
		TryUpdateModules();

		auto it = std::upper_bound(s_modules.begin(), s_modules.end(), addr,
		                           [] (const uint64 value, const Module& m) {
			                           return value < m.Base();
		                           });

		if (it == s_modules.begin()) {
			return nullptr;
		}

		--it;
		if (addr >= it->Base() && addr < it->End()) {
			return &*it;
		}

		return nullptr;
	}

	void InitializeModules()
	{
		if (s_cookie) {
			printf("Init failed. Modules Utility is already initialized!!\n");
			return;
		}

		const HMODULE ntdll     = GetModuleHandle(L"ntdll.dll");
		const auto register_dll = reinterpret_cast<LdrRegisterDllNotification_t>(GetProcAddress(ntdll, "LdrRegisterDllNotification"));
		if (!register_dll) {
			printf("Failed to get LdrRegisterDllNotification\n");
			return;
		}

		if (register_dll(0, reinterpret_cast<PVOID>(&DllNotify), nullptr, &s_cookie) < 0) {
			printf("Failed to register DllNotify\n");
			return;
		}

		s_dirty.store(true, std::memory_order_relaxed);
		printf("Successfully registered DllNotify\n");

		TryUpdateModules();
	}

	void UninitializeModules()
	{
		if (!s_cookie) {
			return;
		}

		const HMODULE ntdll       = GetModuleHandle(L"ntdll.dll");
		const auto unregister_dll = reinterpret_cast<LdrUnregisterDllNotification_t>(GetProcAddress(ntdll, "LdrUnregisterDllNotification"));
		if (!unregister_dll) {
			printf("Failed to get LdrUnregisterDllNotification\n");
			return;
		}

		if (unregister_dll(s_cookie)) {
			printf("Failed to unregister DllNotify\n");
			return;
		}

		s_cookie = nullptr;
	}
}

