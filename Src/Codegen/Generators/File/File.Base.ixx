// Hazno - 2026

module;

#include <inja/json.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.File:Base;
import Atlas.Common;
import std;

export namespace Atlas::Codegen
{
	struct GeneratedFile
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(GeneratedFile, Path_Relative, Data)

		std::string Path_Relative;
		inja::json Data;
	};
}
