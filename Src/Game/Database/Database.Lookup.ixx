// Hazno - 2026

export module Atlas.Game.Database:Lookup;
import Atlas.Common;
import std;
import frozen;

export namespace Atlas::Database
{
	struct LookupMeta
	{
		const char* Name;
		const char* Comment;
		int test;
	};

	inline constexpr frozen::unordered_map<uint64, LookupMeta, 1> olaf = {
			{0x00000000BFD9AADD, {"s", "t", 1}},
	};
}
