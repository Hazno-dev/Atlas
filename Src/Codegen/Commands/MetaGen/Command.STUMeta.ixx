// Hazno - 2026

module;

#include <fast-cpp-csv-parser/csv.h>
#include <inja/inja.hpp>
#include <nlohmann/json.hpp>

export module Atlas.Codegen.Command:STUMeta;
import :Base;
import Atlas.Common;
import Atlas.Codegen.File;
import Atlas.Codegen.Definition;
import Atlas.Resources;
import Atlas.Database.Probe;

export namespace Atlas::Codegen
{
	//TODO: Make it generic for any meta type, not just STU
	class STUMetaProcess : public Command
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
				ModuleFile file("Database:STUMeta", "Database");
				file.Imports.insert(file.Imports.end(), {
						                    ":Lookup",
						                    "Atlas.Common",
						                    "frozen"});

				StructDefinition struc("DBMeta_STUData");
				struc.Members.insert(struc.Members.end(), {
						                     MemberField("Name", "const char*"),
						                     MemberField("Path", "const char*"),
						                     MemberField("Hash", "const uint64")});
				file.Structs.push_back(struc);

				std::stringstream hashLookup, nameLookup;
				hashLookup << "{\n";
				nameLookup << "{\n";
				uint32 count = 0;

				io::CSVReader<3, io::trim_chars<' '>, io::no_quote_escape<','>, io::throw_on_overflow, io::single_and_empty_line_comment<';'>>
						csv(nullptr, std::make_unique<io::detail::NonOwningStringByteSource>(atlas_meta.c_str(), atlas_meta.size()));
				std::string name, path, hash;
				csv.read_row(name, path, hash); //skip header
				while (csv.read_row(name, path, hash)) {
					hashLookup << "    { 0x" << hash <<   ", {\"" << name << "\", \"" << path << "\", 0x" << hash << "} }," << std::endl;
					nameLookup << "    { \"" << name << "\", {\"" << name << "\", \"" << path << "\", 0x" << hash << "} }," << std::endl;
					count++;
				}

				hashLookup << "}})";
				nameLookup << "}})";

				file.Fields.insert(file.Fields.end(),
				                   {
						                   MemberField("c_stuData_hash",
						                               std::format("inline constexpr frozen::unordered_map<uint64, DBMeta_STUData, {}>", count),
						                               std::format("frozen::make_unordered_map(std::array<std::pair<uint64, DBMeta_STUData>, {}>{{", count) + hashLookup.str()),
						                   MemberField("c_stuData_name",
						                               std::format("inline constexpr frozen::unordered_map<frozen::string, DBMeta_STUData, {}>", count),
						                               std::format("frozen::make_unordered_map(std::array<std::pair<frozen::string, DBMeta_STUData>, {}>{{", count) + nameLookup.str())});

				file.Functions.insert(file.Functions.end(),
				                      {
						                      FunctionDefinition("GetMeta", "auto&", "const uint64 lookup", "constexpr",
						                      	"<Database_EntryType::STU>", "", "<>",
						                      	"return c_stuData_hash.at(lookup);"),
						                      FunctionDefinition("GetMeta", "auto&", "const std::string_view lookup", "constexpr",
						                                         "<Database_EntryType::STU>", "", "<>",
						                                         "return c_stuData_name.at(lookup);")}
					);

				file.WriteToFile("Src/Core/Database/Meta/Meta.STU.ixx");
			}
	};
}
