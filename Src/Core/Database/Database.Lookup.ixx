// Hazno - 2026

export module Atlas.Database:Lookup;
import Atlas.Common;
import std;

enum class Database_EntryType
{
	STU,
};

export namespace Atlas::Database
{
	template<Database_EntryType E>
	constexpr auto& GetMeta(uint64 lookup) = delete;

	template<Database_EntryType E>
	constexpr auto& GetMeta(std::string_view lookup) = delete;
}
