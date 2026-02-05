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

	void ListResources(std::vector<std::string>& targetList, const std::string& directory, const std::string& extension_filter)
	{
		if (!s_filesystem.exists(directory)) {
			throw std::runtime_error("Resource directory does not exist: " + directory);
		}

		if (!s_filesystem.is_directory(directory)) {
			throw std::runtime_error("Resource directory not found: " + directory);
		}

		for (const auto& entry : s_filesystem.iterate_directory(directory)) {
			if (const auto target = directory + '/' + entry.filename(); s_filesystem.is_file(target)) {
				if (extension_filter.empty() || entry.filename().ends_with(extension_filter)) {
					targetList.push_back(target);
				}
			} else {
				ListResources(targetList, target, extension_filter);
			}
		}
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
