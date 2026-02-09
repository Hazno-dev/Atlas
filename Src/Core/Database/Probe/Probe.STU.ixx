// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Database.Probe:STU;
import :Hex;
import std;
import Atlas.Game.STU.RTTI;

export namespace Atlas::Probe
{
	struct Data_STUArgument
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Data_STUArgument, Name, Hash, Offset, TypeName, TypeHash, TypeFlag)

		std::string Name;

		Data_UHex64 Hash;
		Data_UHex64 Offset;

		std::string TypeName;
		Data_UHex64 TypeHash;
		Data_UHex64 TypeFlag;

		Data_STUArgument() = default;

		explicit Data_STUArgument(const STU::STUArgumentInfo* arg);
	};

	struct Data_STUInfo
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Data_STUInfo, Name, Hash, ParentHash, RVA, RegistryRVA, Size, IsArray, ArgumentCount, Arguments)

		std::string Name;

		Data_UHex64 Hash;
		Data_UHex64 ParentHash;

		Data_UHex64 RVA;
		Data_UHex64 RegistryRVA;

		uint64 Size;

		int32 ArgumentCount;
		std::vector<Data_STUArgument> Arguments;

		bool IsArray;

		Data_STUInfo() = default;

		explicit Data_STUInfo(const STU::STURegistry* registry);
		explicit Data_STUInfo(const STU::STUInfo* info);
	};
}
