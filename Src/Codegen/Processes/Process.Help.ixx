// Hazno - 2026

export module Atlas.Codegen.Process:Help;
import :Base;
import std;

export namespace Atlas::Codegen
{
	class HelpProcess : public Process
	{
		public:
			ATLAS_NODISCARD constexpr const char* GetHelpArguments() override
			{
				return "--help, -h - Display this help message.";
			}

			ATLAS_NODISCARD constexpr bool IsBlocking() override
			{
				return true;
			}

			void UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				if (arg == "--help" || arg == "-h") {
					m_shouldRun = true;
				}
			}

			void Run(CodegenInstance* instance) override
			{
				auto processes = GetProcesses();
				std::cout << "--- Atlas Codegen" << std::endl << std::endl;
				std::cout << "  - Arguments:" << std::endl;
				for (const auto& process : processes) {
					std::cout << "	" << process->GetHelpArguments() << std::endl;
				}
			}
	};
}
