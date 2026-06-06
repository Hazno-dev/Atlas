// Hazno - 2026

module;

#define ATLAS_DEFINE_HASHMAP(type, name)																	\
	HashDataMap<type> name;																					\
	template <DatabaseType T> requires T == type															\
	constexpr HashDataMap<type>& GetDatabase()													\
	{																										\
		return name;																						\
	}

export module Atlas.Database.Hash:Database;
import Atlas.Database.Type;
import Atlas.Database.Reference;
import :Data;
import std;

export namespace Atlas::DB
{
	struct HashDB
	{
		private:
			ATLAS_DEFINE_HASHMAP(STUHash, m_stuHash);

		public:
			template <DatabaseType T, typename... Args>
			bool Add(Args&&... args) requires requires (Args&&... args) { GetDatabase<T>().Add(std::forward<Args>(args)...); }
			{
				return GetDatabase<T>().Add(std::forward<Args>(args)...);
			}

			template <DatabaseType T, typename Arg>
			bool Remove(Arg&& arg) requires requires (Arg&& arg) { GetDatabase<T>().Remove(std::forward<Arg>(arg)); }
			{
				return GetDatabase<T>().Remove(std::forward<Arg>(arg));
			}

			template <DatabaseType T, typename Arg>
			DataRef<HashData<T>> Get(Arg&& arg) requires requires (Arg&& arg) { GetDatabase<T>().Get(std::forward<Arg>(arg)); }
			{
				return {GetDatabase<T>().Get(std::forward<Arg>(arg))};
			}

			template <DatabaseType T, typename Arg>
			bool Contains(Arg&& arg) const requires requires (Arg&& arg) { GetDatabase<T>().Contains(std::forward<Arg>(arg)); }
			{
				return GetDatabase<T>().Contains(std::forward<Arg>(arg));
			}
	};
}
