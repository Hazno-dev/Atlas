// Hazno - 2026

module;

#include <inja/inja.hpp>

export module Atlas.Codegen;
import Atlas.Resources;
import std;

export namespace Atlas::Codegen
{
	struct CodegenInstance
	{
		//Settings
		std::filesystem::path BindingPath;
		std::filesystem::path RepoPath;

		bool IncludeSTUNames = false;
	};

	inja::Environment* GetEnvironment();
}
