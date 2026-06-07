// Hazno - 2026

module;

#define ATLAS_DEFINE_DATABASE(type, name, ...)															\
	type name;																							\
	template <DatabaseType T>  requires (Cpt_Equals<T, __VA_ARGS__>)									\
	constexpr type& GetDB()&																			\
	{																									\
		return name;																					\
	}

#define ATLAS_DB_OP(name)																				\
template <DatabaseType TargetDB, typename... Args> requires requires {\
GetDB<TargetDB>().template name<TargetDB>(std::declval<Args>()...);\
}																\
	constexpr decltype(auto) name(Args&&... args)														\
	{																									\
		return GetDB<TargetDB>().template name<TargetDB>(std::forward<Args>(args)...);					\
	}

export module Atlas.Database:Instance;
import Atlas.Database.Type;
import Atlas.Database.Hash;
import std;

export namespace Atlas::DB
{
	class Instance
	{
		ATLAS_DEFINE_DATABASE(HashDB, m_hashDatabase, STUHash);

		public:
			ATLAS_DB_OP(Add)
			ATLAS_DB_OP(Remove)
			ATLAS_DB_OP(Get)
			ATLAS_DB_OP(Contains)
	};
}

enum struct C { final, import, module };

static_assert(std::is_scoped_enum_v<C> == true);
static_assert(std::is_same<std::make_unsigned<int32>::type, uint32>::value == true);

static constexpr void test()
{
	auto db = new Atlas::DB::Instance(); //ignore


	auto didAdd = db->Add<Atlas::DB::STUHash>("STUSomething", 0x8338787);
	didAdd = db->Add<Atlas::DB::STUHash>("STUSomething", "My Description", 0x8338787);
	didAdd = db->Add<Atlas::DB::STUHash>("STUSomething", "My Description", 0x8338787, Atlas::VersionBounds(13824, 0));
	auto myStu = db->Get<Atlas::DB::STUHash>(0x8338787);
	auto myStuByString = db->Get<Atlas::DB::STUHash>("STUSomething");
	auto hasMyStu = db->Contains<Atlas::DB::STUHash>(0x8338787);
	auto hasMyStuByString = db->Contains<Atlas::DB::STUHash>("STUSomething");
	auto didRemoveByHash = db->Remove<Atlas::DB::STUHash>(0x8338787);
	auto didRemoveByString = db->Remove<Atlas::DB::STUHash>("STUSomething");
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
