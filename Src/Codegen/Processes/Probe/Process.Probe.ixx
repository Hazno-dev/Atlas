// Hazno - 2026

module;

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.Process:Extraction;
import :Base;
import Atlas.Codegen.ProbeGen;
import Atlas.Resources;
import Atlas.Game.Database.Probe;

static_assert(boost::describe::has_describe_members<Atlas::Probe::Data_Root>::value, "FLOP");
using DataMembers = boost::describe::describe_members<Atlas::Probe::Data_Root, boost::describe::mod_public>;

export namespace Atlas::Codegen
{
	class ProbeGenProcess : public Process
	{
		public:
			ATLAS_NODISCARD constexpr const char* GetHelpArguments() override
			{
				return "--probe=... -p=... - Set the path to the probe (JSON) source and perform probe generation.";
			}

			void UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				const auto assign_pos = arg.find('=');

				if (const auto command = arg.substr(0, assign_pos + 1); command == "--probe=" || command == "-p=") {
					instance->BindingPath = arg.substr(assign_pos + 1);
					if (!std::filesystem::exists(instance->BindingPath)) {
						std::cerr << "Probe file does not exist: " << instance->BindingPath << std::endl;
						return;
					}
					if (instance->BindingPath.extension() != ".json") {
						std::cerr << "Probe file must be a .json file: " << instance->BindingPath << std::endl;
						return;
					}

					m_shouldRun = true;
				}
			}

			void Run(CodegenInstance* instance) override
			{
				std::ifstream file(instance->BindingPath, std::ios::in);
				if (!file.is_open()) {
					throw std::runtime_error("Failed to open binding json file: " + instance->BindingPath.string());
				}

				std::vector<std::string> resource_list{};
				Resources::ListResources(resource_list, "Templates", ".inja");

				auto env = GetEnvironment();
				env->add_callback("newline", 0, [] (inja::Arguments& args) {
					return "\\n";
				});

				env->set_trim_blocks(true);
				env->set_throw_at_missing_includes(false);
				env->set_include_callback([] (const std::filesystem::path&, const std::string& template_name) {
					const std::string res_content = Resources::LoadResource("Templates/" + template_name);
					return GetEnvironment()->parse(res_content);
				});

				for (auto entry : resource_list) {
					const std::string res_content = Resources::LoadResource(entry);
					auto templ = env->parse(res_content);
					entry = entry.substr(std::string("Templates/").length());
					env->include_template(entry, templ);
				}

				inja::json jf = nlohmann::ordered_json::parse(file);

				boost::mp11::mp_for_each<DataMembers>([&]<typename t_data> (t_data D) {
					GenerateProbe<decltype(D.pointer)>(instance, jf[D.name]);
				});
			}
	};
}
