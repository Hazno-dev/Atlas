// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen;
export import :Instance;
import std;

export namespace Atlas::Codegen
{
	int Run(CodegenSettings* settings);
	inja::Environment* GetEnvironment();

	template <typename t_data>
	void Generate(CodegenSettings* settings, inja::json& json)
	{
		static_assert(sizeof(t_data) == 0, "Generate is not specialized for this type");
	}
}
