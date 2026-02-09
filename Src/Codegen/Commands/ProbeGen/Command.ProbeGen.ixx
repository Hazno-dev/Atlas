// Hazno - 2026

module;

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.Command:ProbeGen;
import :Base;
import Atlas.Codegen.ProbeGen;
import Atlas.Resources;
import Atlas.Database.Probe;

static_assert(boost::describe::has_describe_members<Atlas::Probe::Data_Root>::value, "FLOP");
using DataMembers = boost::describe::describe_members<Atlas::Probe::Data_Root, boost::describe::mod_public>;

export namespace Atlas::Codegen
{
	class ProbeGenProcess : public Command
	{
		public:
			ATLAS_NODISCARD constexpr void PrintHelpArguments() override
			{
				std::cout << c_helpGap << "--probe=... -p=... - Set the path to the probe (JSON) source and perform probe generation." << std::endl;
			}

			bool UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				const auto assign_pos = arg.find('=');
				if (const auto command = arg.substr(0, assign_pos + 1); command == "--probe=" || command == "-p=") {
					instance->BindingPath = arg.substr(assign_pos + 1);
					if (!std::filesystem::exists(instance->BindingPath)) {
						std::cerr << "Probe file does not exist: " << instance->BindingPath << std::endl;
						return false;
					}
					if (instance->BindingPath.extension() != ".json") {
						std::cerr << "Probe file must be a .json file: " << instance->BindingPath << std::endl;
						return false;
					}

					m_shouldRun = true;
					return true;
				}

				return true;
			}

			void Run(CodegenInstance* instance) override
			{
				std::ifstream file(instance->BindingPath, std::ios::in);
				if (!file.is_open()) {
					throw std::runtime_error("Failed to open binding json file: " + instance->BindingPath.string());
				}

				inja::json jf = nlohmann::ordered_json::parse(file);

				boost::mp11::mp_for_each<DataMembers>([&]<typename t_data> (t_data D) {
					GenerateProbe<decltype(D.pointer)>(instance, jf[D.name]);
				});
			}
	};
}
