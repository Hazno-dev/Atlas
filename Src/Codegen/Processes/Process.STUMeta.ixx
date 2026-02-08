// Hazno - 2026


module;

#include <boost/describe.hpp>
#include <boost/mp11.hpp>
#include <fast-cpp-csv-parser/csv.h>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.Process:STUMeta;
import :Base;
import Atlas.Codegen.File;
import Atlas.Codegen.Definition;
import Atlas.Resources;
import Atlas.Game.Database.Probe;
import fmt;

export namespace Atlas::Codegen
{
	class STUMetaProcess : public Process
	{
		public:
			ATLAS_NODISCARD constexpr const char* GetHelpArguments() override
			{
				return "--stu-meta -sm - Perform STU Meta code generation.";
			}

			void UpdateArguments(CodegenInstance* instance, const std::string& arg) override
			{
				if (arg == "--stu-meta" || arg == "-sm") {
					m_shouldRun = true;
				}
			}

			void Run(CodegenInstance* instance) override
			{
				auto atlas_meta = Resources::LoadResource("Database/Meta/Meta.STU.csv");
				ModuleFile file("Game.Database:STUMeta", "Database");

				StructDefinition struc("DBMeta_STUData");
				struc.Members.insert(struc.Members.end(), {
						                     MemberField("Name", "const char*"),
						                     MemberField("Path", "const char*"),
						                     MemberField("Hash", "uint64")});

				std::stringstream computed = std::stringstream() << "{\n";
				int count;
				io::CSVReader<3, io::trim_chars<' ', '\t'>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_and_empty_line_comment<';'>>
						csv(atlas_meta);
				std::string name, path, hash;
				while (csv.read_row(name, path, hash)) {
					computed << "	{ 0x" << hash << ", {\"" << name << "\", \"" << path << "\", 0x" << hash << "} },\n";
					count++;
				}
				computed << "};";

				file.Fields.insert(file.Fields.end(),
				                   MemberField("c_stuData", fmt::format("inline constexpr frozen::unordered_map<uint64, DBMeta_STUData, {}>", count),
				                               computed.str()));
				file.GenerateToFile("Src/Game/Database/Meta/Meta.STU.ixx");
			}
	};
}
