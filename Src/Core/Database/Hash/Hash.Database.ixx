// Hazno - 2026

module;

#define ATLAS_DEFINE_HASHMAP(type, name)																	\
	HashDataMap<type> name;																					\
	template <DatabaseType T> requires T == type															\
	constexpr const HashDataMap<type>& GetDatabase() const													\
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
			/*template <DatabaseType T> requires T == STUHash
			DataRef<HashData<T>> Get(uint32 hash)
			{
				const auto& hashMap = GetDatabase<T>();
				auto it = hashMap.find(hash);
				if (it != hashMap.end()) {
					return {it->second};
				}

				return {};
			}

			template <DatabaseType T> requires T == STUHash
			DataRef<HashData<T>> Get(std::string_view str)
			{
				const auto& hashMap = GetDatabase<T>();
				const auto hash = std::hash<std::string_view>{}(str);
				auto it = hashMap.find(hash);
				if (it != hashMap.end()) {
					return {it->second};
				}

				return {};
			}

			template <DatabaseType T, typename Arg>
			constexpr DataRef<HashData<T>> Get(Arg&& arg)
			{
				if constexpr (std::is_same_v<std::decay_t<Arg>, std::string_view>) {
					return {GetDatabase<T>()->GetHashData(std::forward<Arg>(arg))};
				} else if constexpr (std::is_integral_v<std::decay_t<Arg>>) {
					return {GetDatabase<T>()->GetHashData(static_cast<uint64>(arg))};
				} else {
					static_assert(false, "Unsupported lookup type");
					return {};
				}
			}*/
			template <DatabaseType T, typename Arg>
			constexpr DataRef<HashData<T>> Get(Arg&& arg)
			{
				if constexpr (std::same_as<std::make_unsigned<std::decay_t<Arg>>, uint64>
					|| std::same_as<std::make_unsigned<std::decay_t<Arg>>, uint32>) {
					return {GetDatabase<T>().GetHashData(static_cast<uint64>(arg))};
				}

				return {GetDatabase<T>().GetHashData(std::forward<Arg>(arg))};
			}
	};
}
