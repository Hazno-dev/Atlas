// Hazno - 2026

module;

#include <inja/inja.hpp>

module Atlas.Codegen;
import Atlas.Resources;
import std;

namespace Atlas::Codegen
{
	inja::Environment* GetEnvironment()
	{
		static inja::Environment env = [] {
			inja::Environment e;
			std::vector<std::string> resource_list{};
			Resources::ListResources(resource_list, "Templates", ".inja");

			e.set_throw_at_missing_includes(false);
			e.set_include_callback([&e] (const std::filesystem::path&, const std::string& template_name) {
				const std::string res_content = Resources::LoadResource("Templates/" + template_name);
				return e.parse(res_content);
			});

			for (auto entry : resource_list) {
				const std::string res_content = Resources::LoadResource(entry);
				auto templ = e.parse(res_content);
				entry = entry.substr(std::string("Templates/").length());
				e.include_template(entry, templ);
			}

			return e;
		}();
		return &env;
	}
}
