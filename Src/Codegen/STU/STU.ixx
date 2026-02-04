// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen:STU;

export namespace Atlas::Codegen
{
	void Test()
	{
		inja::json data;
		data["name"] = "world";

		auto test = inja::render("Hello {{ name }}!", data);
		printf(test.c_str());
		//
		// inja::Environment env{};
		// env.include_template("base", env.parse_template("F:/Prometheus/Atlas/Src/Codegen/Templates/Base.Module.ixx.inja"));
		// auto cur    = env.parse_template("F:/Prometheus/Atlas/Src/Codegen/Templates/STU.ixx.inja");
		// auto result = env.render(cur, data);
		// printf("%s\n", result.c_str());
	}
}
