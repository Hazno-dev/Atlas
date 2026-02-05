// Hazno - 2026

import Atlas.Codegen;
import std;


void PrintHelp()
{
	std::cout << "--- Atlas Codegen" << std::endl << std::endl;
	std::cout << "  - Arguments:" << std::endl;
	std::cout << "	--binding=... -b=... - Set the path to the binding source." << std::endl;
	std::cout << "	--help -h - Display help message" << std::endl;
}

int main(int argc, char* argv[])
{
	Atlas::Codegen::CodegenSettings config{};

	if (argc < 2) {
		PrintHelp();
		return 1;
	}

	for (int i = 1; i < argc; ++i) {
		std::string arg       = argv[i];
		const auto assign_pos = arg.find('=');
		if (auto command = arg.substr(0, assign_pos + 1); command == "--binding=" || command == "-b=") {
			config.BindingPath = arg.substr(assign_pos + 1);
			if (!std::filesystem::exists(config.BindingPath)) {
				std::cerr << "Binding file does not exist: " << config.BindingPath << std::endl;
				return 1;
			}
		} else if (command == "--help" || command == "-h") {
			std::cout << "Usage: Codegen --input=<input_path> --output=<output_path> [--overwrite]" << std::endl;
			return 0;
		} else {
			std::cerr << "Unknown argument: " << command << '(' << arg << ')' << std::endl;
			std::cerr << "Use --help for more info" << arg << std::endl;
			return 1;
		}
	}

	try {
		Atlas::Codegen::Run(&config);
	} catch (const std::exception& e) {
		std::cerr << "Codegen failed: " << e.what() << std::endl;
		return 1;
	}
}
