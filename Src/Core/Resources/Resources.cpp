// Hazno - 2026

module;

#include "Resources.h"

module Atlas.Resources;

namespace Atlas::Resources
{
	static cmrc::embedded_filesystem s_filesystem = cmrc::Atlas::Resources::get_filesystem();

	bool DirectoryExists(const std::string& path)
	{
		return s_filesystem.exists(path) && s_filesystem.is_directory(path);
	}

	bool ResourceExists(const std::string& path)
	{
		return s_filesystem.exists(path) && s_filesystem.is_file(path);
	}

	std::string LoadResource(const std::string& path)
	{
		if (!s_filesystem.exists(path)) {
			throw std::runtime_error("Resource path does not exist: " + path);
		}

		if (!s_filesystem.is_file(path)) {
			throw std::runtime_error("Resource not found: " + path);
		}

		const auto file = s_filesystem.open(path);
		return std::string(file.begin(), file.end());
	}
}
