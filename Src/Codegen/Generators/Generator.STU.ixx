// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen.Generators:STU;
import Atlas.Codegen;
import Atlas.Codegen.File;
import Atlas.Codegen.Definition;
import Atlas.Binding.Serialization;
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

	template <>
	void Generate<std::__1::vector<Binding::Data_STUInfo> Binding::Data_Root::*const>(
		CodegenSettings* inst, inja::json& json)
	{
		auto env = GetEnvironment();
		auto templ = env->parse(Resources::LoadResource("Templates/File/Module.inja"));
		auto tes = json.back();

		ModuleFile file{};
		file.Data = tes;
		file.Path_Relative = "/STU/Data/STUInfo.ixx";
		file.Name = tes["Name"];
		file.Namespace = "Atlas::STU";
		file.Structs = {};

		StructDefinition struc{};
		struc.Name = tes["Name"];
		struc.Members = {};

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
		std::cout << res << std::endl;
	}
}
