// Hazno - 2026

import Atlas.Codegen;
import Atlas.Codegen.Process;
import std;

inline constexpr auto c_errInvalidArg = "Invalid arguments. Use --help for more info.";

int main(int argc, char* argv[])
{
	std::cout << "--- Atlas Codegen" << std::endl << std::endl;

	Atlas::Codegen::CodegenInstance config{};

	auto& processes = Atlas::Codegen::GetProcesses();
	processes.insert(processes.end(), {
			                 std::make_shared<Atlas::Codegen::HelpProcess>(),
			                 std::make_shared<Atlas::Codegen::STUMetaProcess>(),
			                 std::make_shared<Atlas::Codegen::ProbeGenProcess>(),
	                 });

	if (argc < 2) {
		std::cerr << c_errInvalidArg << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg = argv[i];
		for (const auto& process : processes) {
			if (!process->UpdateArguments(&config, arg)) {
				std::cerr << c_errInvalidArg << std::endl;
				return 1;
			}
		}
	}

	std::cout << " - Running Processes" << std::endl;

	for (const auto& process : processes) {
		if (!process->ShouldRun(&config)) {
			continue;
		}

		try {
			process->Run(&config);
			if (process->IsBlocking()) {
				break;
			}
		} catch (const std::exception& e) {
			std::cerr << "Process failed: " << e.what() << std::endl;
			return 1;
		}
	}
}
