// Hazno - 2026

module Atlas;
import Atlas.Process;
import std;

namespace Atlas
{
	static std::atomic s_initialized{false};
	static std::atomic<Context> s_context{};

	bool IsInitialized()
	{
		return s_initialized.load(std::memory_order_relaxed);
	}

	void Initialize(const Context& context)
	{
		s_context.store(context, std::memory_order_relaxed);
		
		Process::Module::InitializeModules();

		s_initialized.store(true, std::memory_order_relaxed);
	}

	void Uninitialize()
	{
		Process::Module::UninitializeModules();

		s_initialized.store(false, std::memory_order_relaxed);
	}
}
