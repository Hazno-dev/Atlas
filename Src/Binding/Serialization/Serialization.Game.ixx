// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Binding.Serialization:Game;
import :STU;
import std;

namespace Atlas::Binding
{
	struct Data_Game
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Data_Game, STU_Info)

		std::vector<Data_STUInfo> STU_Info;
	};
}
