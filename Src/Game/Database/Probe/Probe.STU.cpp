// Hazno - 2026

module Atlas.Game.Database.Probe;
import Atlas.Game.STU.RTTI;
import Atlas.Process;

namespace Atlas::Probe
{
	Data_STUArgument::Data_STUArgument(const STU::STUArgumentInfo* arg)
	{
		Name = "<unknown>";

		Hash = arg->Hash;
		Offset = arg->Offset;

		if (arg->Constraint) {
			TypeName = "<unknown>";
			TypeHash = arg->Constraint->ExGetSTUType();
			TypeFlag = arg->Constraint->ExToConstraintType();
		}
	}

	Data_STUInfo::Data_STUInfo(const STU::STURegistry* registry) :
		Data_STUInfo(registry->Info)
	{
		RegistryRVA = Process::GetProcessModule().RVA(registry);
	}

	Data_STUInfo::Data_STUInfo(const STU::STUInfo* info)
	{
		Name = "<unknown>";

		Hash = info->Hash;
		ParentHash = info->Parent ? info->Parent->Hash : 0;

		RVA = Process::GetProcessModule().RVA(info);
		RegistryRVA = 0;

		Size = info->InstanceSize;

		IsArray = info->IsArrayInt == 0;

		ArgumentCount = info->ArgsCount;
		Arguments = std::vector<Data_STUArgument>(info->ArgsCount);

		for (const auto arg : info->RangeArgs(false) | std::views::values) {
			Arguments.push_back(Data_STUArgument(arg));
		}
	}
}
