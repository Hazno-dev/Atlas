// Hazno - 2026

export module Atlas.Codegen.Process:Help;
import :Base;
import std;

export namespace Atlas::Codegen
{
	class HelpProcess : public Process
	{
		public:
			ATLAS_NODISCARD constexpr void PrintHelpArguments() override
			{
				std::cout << c_helpGap << "--root=..., -r=... - Set the root path for file generation." << std::endl;
				std::cout << c_helpGap << "--help, -h - Display this help message." << std::endl;
			}

			ATLAS_NODISCARD constexpr bool IsBlocking() override
			{
				return true;
			}

			bool UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				if (arg == "--help" || arg == "-h") {
					m_shouldRun = true;
					return true;
				}

				const auto assign_pos = arg.find('=');
				if (const auto command = arg.substr(0, assign_pos + 1); command == "--root=" || command == "-r=") {
					instance->RepoPath = arg.substr(assign_pos + 1);
					if (!std::filesystem::exists(instance->RepoPath)) {
						std::cerr << "Root path does not exist: " << instance->RepoPath << std::endl;
						return false;
					}
					if (!std::filesystem::is_directory(instance->RepoPath)) {
						std::cerr << "Root path must be a directory: " << instance->RepoPath << std::endl;
						return false;
					}
				}

				return true;
			}

			void Run(CodegenInstance* instance) override
			{
				auto processes = GetProcesses();
				std::cout << "  - Arguments:" << std::endl;
				for (const auto& process : processes) {
					process->PrintHelpArguments();
				}
			}
	};
}
