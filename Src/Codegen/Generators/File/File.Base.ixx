// Hazno - 2026

module;

#include <inja/json.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.File:Base;
import Atlas.Common;
import std;

export namespace Atlas::Codegen
{
	struct GeneratedFile
	{
		virtual ~GeneratedFile() = default;

		void WriteToFile(const std::string& path) const
		{
			const auto contents = GenerateContents();

			auto target_path = std::filesystem::path(path);
			target_path = target_path.replace_extension(".Gen" + target_path.extension().string());
			std::filesystem::create_directories(target_path.parent_path());


			std::cout << "Generating file: " << target_path.string() << std::endl;
			//std::cout << contents << std::endl;

			std::ofstream output(target_path, std::ios::out | std::ios::binary | std::ios::trunc);
			if (!output.is_open()) {
				throw std::runtime_error("Failed to open output file: " + target_path.string());
			}

			output << contents;
			output.flush();
		}

		protected:
			virtual const std::string GenerateContents() const = 0;
	};
}
