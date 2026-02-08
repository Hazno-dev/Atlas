// Hazno - 2026

module;

#include <fast-cpp-csv-parser/csv.h>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.Process:STUMeta;
import :Base;
import Atlas.Codegen.File;
import Atlas.Codegen.Definition;
import Atlas.Resources;
import Atlas.Game.Database.Probe;

export namespace Atlas::Codegen
{
	class STUMetaProcess : public Process
	{
		public:
			ATLAS_NODISCARD constexpr void PrintHelpArguments() override
			{
				std::cout << c_helpGap << "--stu-meta -sm - Perform STU Meta code generation." << std::endl;
			}

			bool UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				if (arg == "--stu-meta" || arg == "-sm") {
					m_shouldRun = true;
					return true;
				}

				return true;
			}

			void Run(CodegenInstance* instance) override
			{
				auto atlas_meta = Resources::LoadResource("Database/Meta/Meta.STU.csv");
				ModuleFile file("Game.Database:STUMeta", "Database");
				file.Imports.push_back("frozen");

				StructDefinition struc("DBMeta_STUData");
				struc.Members.insert(struc.Members.end(), {
						                     MemberField("Name", "const char*"),
						                     MemberField("Path", "const char*"),
						                     MemberField("Hash", "uint64")});
				file.Structs.push_back(struc);

				std::stringstream computed = std::stringstream() << "{\n";
				int count;

				io::CSVReader<3, io::trim_chars<' '>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_and_empty_line_comment<';'>>
						csv(nullptr, std::make_unique<io::detail::NonOwningStringByteSource>(atlas_meta.c_str(), atlas_meta.size()));
				std::string name, path, hash;
				csv.read_row(name, path, hash); //skip header
				while (csv.read_row(name, path, hash)) {
					computed << "    { 0x" << hash << ", {\"" << name << "\", \"" << path << "\", 0x" << hash << "} }," << std::endl;
					count++;
				}
				computed << "}";

				file.Fields.insert(file.Fields.end(),
				                   MemberField("c_stuData", std::format("inline constexpr frozen::unordered_map<uint64, DBMeta_STUData, {}>", count),
				                               computed.str()));
				file.GenerateToFile("Src/Game/Database/Meta/Meta.STU.ixx");
			}
	};
}
