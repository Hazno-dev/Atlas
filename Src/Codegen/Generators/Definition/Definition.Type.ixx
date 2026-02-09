// Hazno - 2026

module;

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

export module Atlas.Codegen.Definition:Type;
import :Members;
import Atlas.Common;
import Atlas.Resources;
import Atlas.Codegen;
import std;

export namespace Atlas::Codegen
{
	struct Definition
	{
		std::string Name;
		std::string Specifier;
		std::string Template;
		std::string Comment;

		virtual ~Definition() = default;

		explicit Definition(
			std::string name, std::string specifier = "", std::string templ = "", std::string comment = "") :
			Name(std::move(name)),
			Specifier(std::move(specifier)),
			Template(std::move(templ)),
			Comment(std::move(comment)) {}

		virtual inja::json Serialize() const
		{
			inja::json j;
			j["Name"] = Name;
			if (!Comment.empty()) {
				j["Comment"] = Comment;
			}

			if (!Template.empty()) {
				j["Template"] = Template;
			}
			if (!Specifier.empty()) {
				j["Specifier"] = Specifier;
			}

			return j;
		}
	};

	struct StructDefinition : Definition
	{
		std::vector<MemberField> Members{};

		explicit StructDefinition(
			std::string name, std::string specifier = "", std::string templ = "", std::string comment = "") :
			Definition(std::move(name), std::move(specifier), std::move(templ), std::move(comment)) {}

		inja::json Serialize() const override
		{
			inja::json j = Definition::Serialize();
			j["Members"] = Members;
			return j;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const StructDefinition& nlohmann_json_t)
		{
			static const std::string c_structTemplate = Resources::LoadResource("Templates/Definition/Struct.inja");
			const auto env = GetEnvironment();
			nlohmann_json_j = env->render(c_structTemplate, nlohmann_json_t.Serialize());
		}
	};

	struct FunctionDefinition : Definition
	{
		std::string Return;
		std::string Parameters;
		std::string Body;
		std::string Attributes;
		std::string Specialisation;

		explicit FunctionDefinition(
			std::string name, std::string ret, std::string params, std::string attributes = "",
			std::string specialisation = "", std::string specifier = "", std::string templ = "", std::string body = "", std::string comment = "") :
			Definition(std::move(name), std::move(specifier), std::move(templ), std::move(comment)),
			Return(std::move(ret)),
			Parameters(std::move(params)),
			Body(std::move(body)),
			Attributes(std::move(attributes)),
			Specialisation(std::move(specialisation)) {}

		inja::json Serialize() const override
		{
			inja::json j = Definition::Serialize();
			j["Return"] = Return;

			if (!Parameters.empty()) {
				j["Parameters"] = Parameters;
			}

			if (!Body.empty()) {
				j["Body"] = Body;
			}

			if (!Attributes.empty()) {
				j["Attributes"] = Attributes;
			}

			if (!Specialisation.empty()) {
				j["Specialisation"] = Specialisation;
			}
			return j;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const FunctionDefinition& nlohmann_json_t)
		{
			static const std::string c_functionTemplate = Resources::LoadResource("Templates/Definition/Function.inja");
			const auto env = GetEnvironment();
			nlohmann_json_j = env->render(c_functionTemplate, nlohmann_json_t.Serialize());
		}
	};

	struct EnumDefinition : Definition
	{
		std::vector<MemberEnum> Values;
	};
}
