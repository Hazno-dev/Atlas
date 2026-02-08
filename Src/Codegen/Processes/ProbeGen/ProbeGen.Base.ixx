// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen.ProbeGen:Base;
import Atlas.Codegen;

export namespace Atlas::Codegen
{
	template <typename t_data>
	void GenerateProbe(CodegenInstance* settings, inja::json& json)
	{
		static_assert(sizeof(t_data) == 0, "Generate is not specialized for this type");
	}
}
