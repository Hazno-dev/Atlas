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
		protected:
			std::string Name;
			std::string Comment;

		public:
			virtual ~Member() = default;

			explicit Member(std::string name, std::string comment = "") :
				Name(std::move(name)),
				Comment(std::move(comment)) {}

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
		protected:
			std::string Type;
			std::string Value;
			int64 Offset = -1;

		public:
			explicit MemberField(std::string name, std::string type, std::string value = "", std::string comment = "",
				const int64 offset = -1) :
				Member(std::move(name), std::move(comment)),
				Type(std::move(type)),
				Value(std::move(value)),
				Offset(offset) {}

			MemberField() :
				MemberField("", "") {}

			inja::json Serialize() const override
			{
				inja::json j = Member::Serialize();
				j["Type"] = Type;
				if (!Value.empty()) {
					j["Value"] = Value;
				}
				if (Offset != -1) {
					j["Offset"] = Offset;
				}

				return j;
			}

			template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
			friend void to_json(BasicJsonType& nlohmann_json_j, const MemberField& nlohmann_json_t)
			{
				static const std::string c_fieldTemplate = Resources::LoadResource("Templates/Definition/Member/Field.inja");
				const auto env = GetEnvironment();
				nlohmann_json_j = env->render(c_fieldTemplate, nlohmann_json_t.Serialize()).c_str();
			}
	};

	struct MemberEnum
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(MemberEnum, Name, Value)

		std::string Name;
		std::string Value;
	};
}
