// Hazno - 2026

export module Atlas.Database.Probe:Struct;
import :Hex;
import Atlas.Game.STU.RTTI;
import Atlas.Process;
import std;

namespace Atlas::Probe
{
	struct Data_Struct
	{
		std::string Name;
		std::string ParentName;

		Data_UHex64 VA;

		uint64 Size;
		Data_UHex64 Hash;
	};
}
