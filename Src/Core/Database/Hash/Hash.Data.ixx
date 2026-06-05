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
			const Serialisation::UHex64 m_hash;
			const std::string m_text;
			const std::string m_description;

			const VersionBounds m_versionBounds;

		public:
			HashData(const char* text, const char* description, const uint64 value) :
				m_hash(value),
				m_text(text),
				m_description(description) {}

			HashData(std::string text, std::string description, const uint64 value) :
				m_hash(value),
				m_text(std::move(text)),
				m_description(std::move(description)) {}

			HashData(const char* text, const char* description, const uint64 value, const VersionBounds versionBounds) :
				m_hash(value),
				m_text(text),
				m_description(description),
				m_versionBounds(versionBounds) {}

			HashData(std::string text, std::string description, const uint64 value, const VersionBounds versionBounds) :
				m_hash(value),
				m_text(std::move(text)),
				m_description(std::move(description)),
				m_versionBounds(versionBounds) {}

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

			static constexpr uint64 FNV1a(const char* str, const size_t n)
			{
				uint64 hash = 14695981039346656037ull;
				for (size_t i = 0; i < n; ++i) {
					hash ^= static_cast<uint8>(str[i]);
					hash *= 1099511628211ull;
				}
				return hash;
			}

		public:
			const HashData<Type>* GetHashData(uint64 hash) const
			{
				const auto it = m_canonicalMap.find(hash);
				if (it != m_canonicalMap.end()) {
					return &it->second;
				}

				return nullptr;
			}

			/*
			const HashData<Type>* GetHashData(std::string_view str) const
			{
				const auto hash = FNV1a(str.data(), str.size());
				const auto it = m_hashStringLookup.find(hash);
				if (it != m_hashStringLookup.end()) {
					const auto canonicalID = it->second;
					return GetHashData(canonicalID);
				}

				return nullptr;
			}

			template <size_t N>
			const HashData<Type>* GetHashData(const char (&str)[N]) const
			{
				constexpr uint64 hash = FNV1a(str, N - 1);

				const auto it = m_hashStringLookup.find(hash);
				if (it != m_hashStringLookup.end()) {
					const auto canonicalID = it->second;
					return GetHashData(canonicalID);
				}

				return nullptr;
			}*/
	};
}
