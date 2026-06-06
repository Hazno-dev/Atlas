// Hazno - 2026

export module Atlas.Database.Type;
import std;

export namespace Atlas::DB
{
	enum DatabaseType
	{
		STUHash = 1,
		STUHSash,
		STUHSSash,
	};

	template <DatabaseType T, typename Database, typename... Args>
	concept DatabaseLookup = requires (Database db, Args&&... args) {
		db.template Add<T>(std::forward<Args>(args)...);
		db.template Remove<T>(std::forward<Args>(args)...);
		db.template Get<T>(std::forward<Args>(args)...);
		db.template Get<T>(std::forward<Args>(args)...);
	};
}
