// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Context:Versioning;

import Atlas.Common;
import std;

export namespace Atlas
{
	struct VersionBounds
	{
		NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(VersionBounds, Min, Max)

		const uint32 Min{0}, Max{0};

		VersionBounds() = default;

		VersionBounds(const uint32 min, const uint32 max) :
			Min(min),
			Max(max) {}

		bool operator()(const uint32 version) const
		{
			return Contains(version);
		}

		bool Contains(const uint32 version) const
		{
			return (!Min || version >= Min) && (!Max || version <= Max);
		}

		bool IsDefault() const
		{
			return Min == 0 && Max == 0;
		}
	};
}
