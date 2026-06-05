// Hazno - 2026

module;

#define ATLAS_DEFINE_DATABASE(type, name, ...)															\
	type name;																							\
	template <DatabaseType T>  requires (Cpt_Equals<T, __VA_ARGS__>)									\
	constexpr type& GetDB()&																			\
	{																									\
		return name;																					\
	}

#define ATLAS_DATABASE_CPT_NO_SPEC(name)																\
	template <typename TargetDB, typename... Args>														\
	requires (requires (Atlas::DB::Instance* inst, Args&&... args) {									\
		inst->template GetDatabase<TargetDB>()->name(std::forward<Args>(args)...);						\
	} || requires (Args&&... args) {																	\
		TargetDB::name(std::forward<Args>(args)...);													\
	})

#define ATLAS_DATABASE_CPT_SPEC(name)																	\
	template <typename TargetDB, auto Specifier, typename... Args>										\
	requires (requires(Instance* inst, Args&&... args) {												\
		inst->template GetDatabase<TargetDB>()->template name<Specifier>(std::forward<Args>(args)...);	\
	} || requires(Args&&... args) {																		\
		TargetDB::template name<Specifier>(std::forward<Args>(args)...);								\
	})

export module Atlas.Database:Instance;
import Atlas.Database.Type;
import Atlas.Database.Hash;
import std;

export namespace Atlas::DB
{
	/*template <DatabaseType T, typename... Args>
	concept DatabaseLookup = requires (Args&& args) {
		{ GetDB<T>::GetSize(value, state) } -> std::convertible_to<u32>;
		{ GetDB<T>::WriteToBuffer(value, state, buffer) } -> std::same_as<void>;
	};
	*/

	class Instance
	{
		public:
			ATLAS_DEFINE_DATABASE(HashDB, m_hashDatabase, STUHash);

			/*
			ATLAS_DATABASE_CPT_NO_SPEC(Get)
			constexpr decltype(auto) Get(Args&&... args)
			{
				if constexpr (requires { GetDatabase<TargetDB>()->Get(std::forward<Args>(args)...); }) {
					return GetDatabase<TargetDB>()->Get(std::forward<Args>(args)...);
				} else if constexpr (requires { TargetDB::Get(std::forward<Args>(args)...); }) {
					return TargetDB::Get(std::forward<Args>(args)...);
				}
			}

			ATLAS_DATABASE_CPT_SPEC(Get)
			constexpr decltype(auto) Get(Args&&... args)
			{
				if constexpr (requires { GetDatabase<TargetDB>()->template Get<Specifier>(std::forward<Args>(args)...); }) {
					return GetDatabase<TargetDB>()->template Get<Specifier>(std::forward<Args>(args)...);
				} else if constexpr (requires { TargetDB::template Get<Specifier>(std::forward<Args>(args)...); }) {
					return TargetDB::template Get<Specifier>(std::forward<Args>(args)...);
				}
			}
			*/

			template <DatabaseType TargetDB, typename... Args> requires requires (Args&&... args) {
				GetDB<TargetDB>().template Get<TargetDB>(std::forward<Args>(args)...);
			}
			constexpr decltype(auto) Get(Args&&... args)
			{
				return GetDB<TargetDB>().template Get<TargetDB>(std::forward<Args>(args)...);
			}
	};
}

enum struct C { final, import, module };

static_assert(std::is_scoped_enum_v<C> == true);
static_assert(std::is_scoped_enum_v<Atlas::DB::STUHash> == true);

static constexpr void test()
{
	auto tet = new Atlas::DB::Instance();
	auto ress = tet->Get<Atlas::DB::STUHash>("G");
	//ress->GetHash();
	auto res = tet->Get<Atlas::DB::HashDB, Atlas::DB::HashType::STU>("0x839983982876876");
	if constexpr (requires { tet->GetDatabase<Atlas::DB::HashDB>()->template Get<Atlas::DB::HashType::STU>("test"); }) {
		auto res2 = tet->GetDatabase<Atlas::DB::HashDB>()->template Get<Atlas::DB::HashType::STU>("test");
	}
	tet->GetDatabase<Atlas::DB::HashDB>()->Get<Atlas::DB::HashType::STU>("test");
}

/*public:
	template <typename BasicJsonType, nlohmann::detail::enable_if_t<
		          nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
	friend void to_json(BasicJsonType& nlohmann_json_j, const Data_UHex64& nlohmann_json_t)
	{
		char buf[32];
		sprintf_s(buf, "%p", nlohmann_json_t.Value);
		nlohmann_json_j = std::string(buf);
	}

	template <typename BasicJsonType, nlohmann::detail::enable_if_t<
		          nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
	friend void from_json(const BasicJsonType& nlohmann_json_j, Data_UHex64& nlohmann_json_t)
	{
		const Data_UHex64 nlohmann_json_default_obj{};
		nlohmann_json_t.Value = !nlohmann_json_j.is_null()
			                        ? _strtoi64(nlohmann_json_j.template get<std::string>().c_str(), nullptr, 16)
			                        : nlohmann_json_default_obj.Value;
}*/

/*
template <DataT::LookupType Type>
DataT::Hash<Type>& GetHash(const char* text) = delete;*/
//};

/*
constexpr auto& GetMeta(Atlas::Instance& inst, std::string_view lookup)
{
	return inst.GetMeta(lookup);
}

}
*/
