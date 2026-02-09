// Hazno - 2026

module;

#include <nlohmann/json.hpp>
#include <boost/describe.hpp>

export module Atlas.Database.Probe:Game;
import :STU;
import std;

export namespace Atlas::Probe
{
	struct Data_Root
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(Data_Root, STU_Info)

		std::vector<Data_STUInfo> STU_Info;
	};

	BOOST_DESCRIBE_STRUCT(Data_Root, (), (STU_Info));
}
