// Hazno - 2026

module;

#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

export module Atlas.Codegen.Definition:Members;
import Atlas.Common;
import Atlas.Resources;
import Atlas.Codegen;

export namespace Atlas::Codegen
{
	struct Member
	{
		std::string Name;
		std::string Comment;

		virtual ~Member() = default;

		virtual inja::json Serialize() const
		{
			inja::json j;
			j["Name"] = Name;
			if (!Comment.empty()) {
				j["Comment"] = Comment;
			}
			return j;
		}
	};

	struct MemberField : Member
	{
		std::string Type;
		std::string Value;
		uint32 Offset;

		inja::json Serialize() const override
		{
			inja::json j = Member::Serialize();
			j["Type"]    = Type;
			if (!Value.empty()) {
				j["Value"] = Value;
			}
			j["Offset"] = Offset;
			return j;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const MemberField& nlohmann_json_t)
		{
			static const std::string c_fieldTemplate = Resources::LoadResource("Templates/Member/Field.inja");
			const auto env                           = GetEnvironment();
			nlohmann_json_j                          = env->render(c_fieldTemplate, nlohmann_json_t.Serialize());
		}
	};

	struct MemberEnum
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MemberEnum, Name, Value)

		std::string Name;
		std::string Value;
	};
}
