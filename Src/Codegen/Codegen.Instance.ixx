// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen:Instance;
import std;

export namespace Atlas::Codegen
{
	struct CodegenSettings
	{
		//Settings
		std::string BindingPath;
	};
}
