// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Codegen.File:Module;
import :Base;
import Atlas.Codegen.Definition;

export namespace Atlas::Codegen
{
	struct ModuleFile : GeneratedFile
	{
		std::string Name;
		std::vector<std::string> Imports;
		std::string Namespace;
		std::vector<StructDefinition> Structs;

		ModuleFile() = default;

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const ModuleFile& nlohmann_json_t)
		{
			nlohmann_json_j["Name"]        = nlohmann_json_t.Name;
			nlohmann_json_j["Imports"]     = nlohmann_json_t.Imports;
			nlohmann_json_j["Namespace"]   = nlohmann_json_t.Namespace;
			nlohmann_json_j["Definitions"] = nlohmann_json_t.Structs;
		}
	};
}
