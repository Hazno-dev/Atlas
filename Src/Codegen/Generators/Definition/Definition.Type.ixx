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
		protected:
			~Definition() = default;

		public:
			const std::string Name;
			const std::string Inheritance;
			const std::string Template;
			const std::string Comment;

			explicit Definition(
				const std::string& name, const std::string& inheritance = "", const std::string& templ = "", const std::string& comment = "") :
				Name(name),
				Inheritance(inheritance),
				Template(templ),
				Comment(comment) {}

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
				if (!Inheritance.empty()) {
					j["Inheritance"] = Inheritance;
				}

				return j;
			}
	};

	struct StructDefinition : Definition
	{
		std::vector<MemberField> Members{};

		explicit StructDefinition(
			const std::string& name, const std::string& inheritance = "", const std::string& templ = "", const std::string& comment = "") :
			Definition(name, inheritance, templ, comment) {}

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

	struct EnumDefinition : Definition
	{
		std::vector<MemberEnum> Values;
	};
}
