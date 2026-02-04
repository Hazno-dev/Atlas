// Hazno - 2026

module Atlas.Game.STU.RTTI;
import Atlas.Process;

namespace Atlas::STU
{
	STUInfo* STURegistry::GetSTUInfoByHash(uint32 hash) const
	{
		auto registry = this;
		while (registry) {
			if (registry->Info && registry->Info->Hash == hash) {
				return registry->Info;
			}

			registry = registry->Next;
		}

		return nullptr;
	}

	STURegistryView STURegistry::Range() const
	{
		return STURegistryView::Create(this);
	}

	STURegistry* STURegistry::Get()
	{
		return Get(Process::GetProcessModule());
	}

	STURegistry* STURegistry::Get(const Process::Module& module)
	{
		return *module.VA<STURegistry* *>(0x18F74E0);
	}
}
