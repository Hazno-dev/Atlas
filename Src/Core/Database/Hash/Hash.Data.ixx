// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Database.Hash:Data;
import Atlas.Database.Type;
import Atlas.Common;
import Atlas.Serialisation;
import Atlas.Context;
import std;

export namespace Atlas::DB
{
	template <DatabaseType Type>
	struct HashData<Type>
	{
		private:
			Serialisation::UHex64 m_hash;
			std::string m_text;
			std::string m_description;

			VersionBounds m_versionBounds;

		public:
			HashData(std::string text, std::string description, const uint64 value) :
				m_hash(value),
				m_text(std::move(text)),
				m_description(std::move(description)) {}

			HashData(std::string text, std::string description, const uint64 value, VersionBounds versionBounds) :
				m_hash(value),
				m_text(std::move(text)),
				m_description(std::move(description)),
				m_versionBounds(std::move(versionBounds)) {}

			uint64 GetHash() const
			{
				return m_hash;
			}

			std::string_view GetText() const
			{
				return m_text;
			}

			std::string_view GetDescription() const
			{
				return m_description;
			}

			const VersionBounds& GetVersionBounds() const
			{
				return m_versionBounds;
			}

			template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
			friend void to_json(BasicJsonType& nlohmann_json_j, const HashData& nlohmann_json_t)
			{
				nlohmann_json_j["Hash"] = nlohmann_json_t.m_hash;
				nlohmann_json_j["Text"] = nlohmann_json_t.m_text;
				nlohmann_json_j["Description"] = nlohmann_json_t.m_description;
				if (!nlohmann_json_t.m_versionBounds.IsDefault()) {
					nlohmann_json_j["Version"] = nlohmann_json_t.m_versionBounds;
				}
			}

			template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
			friend void from_json(const BasicJsonType& nlohmann_json_j, HashData& nlohmann_json_t)
			{
				const HashData nlohmann_json_default_obj{};
				auto text = !nlohmann_json_j.is_null()
					            ? nlohmann_json_j.template get<std::string>()
					            : nlohmann_json_default_obj.m_text;
				auto description = !nlohmann_json_j.is_null()
					                   ? nlohmann_json_j.template get<std::string>()
					                   : nlohmann_json_default_obj.m_description;
				auto hash = !nlohmann_json_j.is_null()
					            ? nlohmann_json_j.template get<uint32>()
					            : nlohmann_json_default_obj.m_hash;
				auto versionBounds = !nlohmann_json_j.is_null() && nlohmann_json_j.contains("Version")
					                     ? nlohmann_json_j.template get<VersionBounds>()
					                     : nlohmann_json_default_obj.m_versionBounds;
			}
	};


	template <DatabaseType Type>
	class HashDataMap<Type>
	{
		private:
			using CanonicalID = uint64;
			std::unordered_map<uint64, HashData<Type>> m_canonicalMap;
			std::unordered_map<uint64, uint64> m_hashStringLookup;

			static constexpr uint64 FNV1a(std::string_view str)
			{
				uint64 hash = 14695981039346656037ull;
				for (const char c : str) {
					hash ^= static_cast<uint8_t>(c);
					hash *= 1099511628211ull;
				}
				return hash;
			}

		public:
			struct CompiledHash
			{
				uint64_t hash;

				template <size_t N>
				consteval CompiledHash(const char (&str)[N]) :
					hash(FNV1a(std::string_view(str, N - 1))) {}

				constexpr CompiledHash(std::string_view str) :
					hash(FNV1a(str)) {}
			};

			template <typename T> requires !Cpt_Ptr<T> && (Cpt_Integral32<T> || Cpt_Integral64<T>)
			const HashData<Type>* Get(T hash) const
			{
				const auto it = m_canonicalMap.find(hash);
				if (it != m_canonicalMap.end()) {
					return &it->second;
				}

				return nullptr;
			}

			const HashData<Type>* Get(CompiledHash cmp) const
			{
				const auto it = m_hashStringLookup.find(cmp.hash);
				if (it != m_hashStringLookup.end()) {
					const auto canonicalID = it->second;
					return Get(canonicalID);
				}

				return nullptr;
			}

			template <typename T> requires !Cpt_Ptr<T> && (Cpt_Integral32<T> || Cpt_Integral64<T>)
			bool Contains(T hash) const
			{
				return m_canonicalMap.contains(hash);
			}

			bool Contains(CompiledHash cmp) const
			{
				return m_hashStringLookup.contains(cmp.hash);
			}

			bool Contains(const HashData<Type>& data) const
			{
				return Contains(data.GetHash()) || Contains(data.GetText());
			}

			bool Add(const HashData<Type>&& data)
			{
				if (Contains(data.GetHash())) {
					return false;
				}

				const auto hash = FNV1a(data.GetText().data(), data.GetText().size());
				const auto it = m_hashStringLookup.find(hash);
				if (it != m_hashStringLookup.end()) {
					return false;
				}

				m_hashStringLookup[hash] = data.GetHash();
				m_canonicalMap[data.GetHash()] = std::move(data);
				return true;
			}

			template <typename... Args> requires std::constructible_from<HashData<Type>, Args&&...> &&
				std::negation_v<std::conjunction<std::is_same<std::decay_t<Args>, HashData<Type>&&>...>>
			bool Add(Args&&... args)
			{
				const HashData<Type> data = HashData<Type>(std::forward<Args>(args)...);
				return Add(std::move(data));
			}

			template <typename T> requires !Cpt_Ptr<T> && (Cpt_Integral32<T> || Cpt_Integral64<T>)
			bool Remove(T hash)
			{
				const auto it = m_canonicalMap.find(hash);
				if (it == m_canonicalMap.end()) {
					return false;
				}

				const auto& data = it->second;
				const auto hashIt = m_hashStringLookup.find(FNV1a(data.GetText()));
				if (hashIt != m_hashStringLookup.end()) {
					m_hashStringLookup.erase(hashIt);
				}

				m_canonicalMap.erase(it);
				return true;
			}

			bool Remove(CompiledHash cmp)
			{
				const auto it = m_hashStringLookup.find(cmp.hash);
				if (it == m_hashStringLookup.end()) {
					return false;
				}

				const auto canonicalID = it->second;
				m_hashStringLookup.erase(it);
				m_canonicalMap.erase(canonicalID);
				return true;
			}
	};
}
