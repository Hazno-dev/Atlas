// Hazno - 2026

module Atlas;
import Atlas.Process;
import std;

namespace Atlas
{
	static std::atomic s_initialized{false};

	bool IsInitialized()
	{
		return s_initialized.load(std::memory_order_relaxed);
	}

	void Initialize()
	{
		Process::Module::InitializeModules();

		s_initialized.store(true, std::memory_order_relaxed);
	}

	void Uninitialize()
	{
		Process::Module::UninitializeModules();

		s_initialized.store(false, std::memory_order_relaxed);
	}
}
