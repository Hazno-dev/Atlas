// Hazno - 2026

module;

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.File:Module;
import :Base;
import Atlas.Codegen;
import Atlas.Codegen.Definition;
import Atlas.Resources;

export namespace Atlas::Codegen
{
	struct ModuleFile : GeneratedFile
	{
		const std::string Name;
		const std::string Namespace;
		std::vector<std::string> Imports{};
		std::vector<StructDefinition> Structs{};
		std::vector<MemberField> Fields{};
		std::vector<FunctionDefinition> Functions{};

		explicit ModuleFile(std::string name, std::string name_space) :
			Name(std::move(name)),
			Namespace(std::move(name_space)) {}

		ModuleFile() :
			Name(""),
			Namespace("") {}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const ModuleFile& nlohmann_json_t)
		{
			nlohmann_json_j["Name"] = nlohmann_json_t.Name;
			nlohmann_json_j["Namespace"] = nlohmann_json_t.Namespace;
			nlohmann_json_j["Imports"] = nlohmann_json_t.Imports;

			nlohmann_json_j["Structs"] = nlohmann_json_t.Structs;
			nlohmann_json_j["Fields"] = nlohmann_json_t.Fields;
			nlohmann_json_j["Functions"] = nlohmann_json_t.Functions;
		}

		protected:
			const std::string GenerateContents() const override
			{
				static const std::string c_structTemplate = Resources::LoadResource("Templates/File/Module.inja");
				const auto env = GetEnvironment();
				const inja::json json = *this;
				return env->render(c_structTemplate, json);
			}
	};
}
