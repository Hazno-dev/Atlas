// Hazno - 2026

export module Atlas.Resources;
import std;

export namespace Atlas::Resources
{
	bool DirectoryExists(const std::string& path);
	bool ResourceExists(const std::string& path);

	template <typename t_ret>
	t_ret LoadResource(const std::string& path)
	{
		static_assert(sizeof(t_ret) == 0, "LoadResource is not specialized for this type");
		return nullptr;
	}

	std::string LoadResource(const std::string& path);
}
