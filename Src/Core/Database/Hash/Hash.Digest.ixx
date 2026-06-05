// Hazno - 2026

module;

#include <nlohmann/json.hpp>
#include <boost/hash2/xxhash.hpp>
#include <boost/hash2/hash_append.hpp>

export module Atlas.Database.Hash:Digest;
import Atlas.Common;

namespace Atlas::DB
{
	struct HashDigest
	{
		private:
			static constexpr uint64 Seed = 32138794905218623941ULL;
			static constexpr uint64 Voodoo = 11400714785074694791ULL;

			uint64 m_digest;

		public:
			void Update(const std::string_view str)
			{
				boost::hash2::xxhash_64 hash{Seed};
				hash.update(str.data(), str.size());

				const auto res = hash.result();
				m_digest += res * Voodoo;
			}

			template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
			friend void to_json(BasicJsonType& nlohmann_json_j, const HashDigest& nlohmann_json_t)
			{
				nlohmann_json_j = nlohmann_json_t.m_digest;
			}

			template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
			friend void from_json(const BasicJsonType& nlohmann_json_j, HashDigest& nlohmann_json_t)
			{
				const HashDigest nlohmann_json_default_obj{};
				nlohmann_json_t.m_digest = !nlohmann_json_j.is_null()
					                           ? nlohmann_json_j.template get<std::string>()
					                           : nlohmann_json_default_obj.m_digest;
			}
	};
}
