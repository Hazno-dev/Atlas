// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen.ProbeGen:STU;
import :Base;
import Atlas.Codegen;
import Atlas.Codegen.File;
import Atlas.Codegen.Definition;
import Atlas.Game.Database.Probe;
import Atlas.Resources;

export namespace Atlas::Codegen
{
	inline constexpr auto c_stuInfo_comment =
			"/**"
			" *  <b> %s </b> \n"
			" *"
			" *  \n"
			" *  \n  Size:           0x%X (%s)"
			" *  \n  RVA:		     0x%s"
			" *  \n  Registry:       0x%s"
			" *  \n  IsArray?        %b"
			" *  \n"
			" */";

	std::string GetSTUTypeName(CodegenInstance* settings, Probe::Data_STUInfo info)
	{
		if (settings->IncludeSTUNames && info.Name != "STUInfo") {
			return info.Name;
		}
	}

	template <>
	void GenerateProbe<std::__1::vector<Probe::Data_STUInfo> Probe::Data_Root::*const>(
		CodegenInstance* settings, inja::json& json)
	{
		/*auto env = GetEnvironment();
		auto templ = env->parse(Resources::LoadResource("Templates/File/Module.inja"));
		auto tes = json.back();

		ModuleFile file{};
		file.Path_Relative = "/STU/Data/STUInfo.ixx";
		file.Name = tes["Name"];
		file.Namespace = "Atlas::STU";

		StructDefinition struc{};
		struc.Name = tes["Name"];
		auto args = tes["Arguments"];
		for (auto arg : args) {
			MemberField field{};
			field.Type = arg["TypeName"];
			field.Name = arg["Name"];
			struc.Members.push_back(field);
		}

		file.Structs.push_back(struc);

		auto res = env->render(templ, file);

		std::cout << "--------------------" << std::endl;
		std::cout << res << std::endl;*/
	}

	void GenerateSTUInfo(CodegenInstance* inst, Probe::Data_STUInfo info)
	{
		/*ModuleFile file{};
		file.Path_Relative = "/STU/Data/STUInfo.ixx";
		file.Name = info.Name;
		file.Namespace = "Atlas::STU";

		StructDefinition struc{};
		struc.Name = tes["Name"];
		auto args = tes["Arguments"];
		for (auto arg : args) {
			MemberField field{};
			field.Type = arg["TypeName"];
			field.Name = arg["Name"];
			struc.Members.push_back(field);
		}

		file.Structs.push_back(struc);

		auto res = env->render(templ, file);*/
	}
}
