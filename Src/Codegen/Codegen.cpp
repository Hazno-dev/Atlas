// Hazno - 2026

module;

#include <inja/inja.hpp>
#include <nlohmann/json.hpp>
#include <boost/describe.hpp>
#include <boost/mp11.hpp>

module Atlas.Codegen;
import Atlas.Codegen.Generators;
import Atlas.Resources;
import Atlas.Binding.Serialization;
import std.compat;

static_assert(boost::describe::has_describe_members<Atlas::Binding::Data_Root>::value, "FLOP");
using DataMembers = boost::describe::describe_members<Atlas::Binding::Data_Root, boost::describe::mod_public>;

namespace Atlas::Codegen
{
	int Run(CodegenSettings* settings)
	{
		std::ifstream file(settings->BindingPath, std::ios::in);
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open binding json file: " + settings->BindingPath);
		}

		std::vector<std::string> resource_list{};
		Resources::ListResources(resource_list, "Templates", ".inja");

		auto env = GetEnvironment();
		env->add_callback("newline", 0, [] (inja::Arguments& args) {
			return "\\n";
		});

		env->set_trim_blocks(true);
		env->set_throw_at_missing_includes(false);
		env->set_include_callback([&settings] (const std::filesystem::path& path, const std::string& template_name) {
			const std::string res_content = Resources::LoadResource("Templates/" + template_name);
			return GetEnvironment()->parse(res_content);
		});

		for (auto entry : resource_list) {
			const std::string res_content = Resources::LoadResource(entry);
			auto templ                    = env->parse(res_content);
			entry                         = entry.substr(std::string("Templates/").length());
			env->include_template(entry, templ);
		}

		inja::json jf = nlohmann::ordered_json::parse(file);

		boost::mp11::mp_for_each<DataMembers>([&]<typename t_data> (t_data D) {
			Generate<decltype(D.pointer)>(settings, jf[D.name]);
		});

		return 0;
	}

	inja::Environment* GetEnvironment()
	{
		static inja::Environment env{};
		return &env;
	}
}
