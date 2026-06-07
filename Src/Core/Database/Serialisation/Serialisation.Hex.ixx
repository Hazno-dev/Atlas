// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Serialisation:Hex;
import Atlas.Common;

export namespace Atlas::Serialisation
{
	struct UHex64
	{
		uint64 Value;

		UHex64() = default;

		UHex64(const uint64 value) :
			Value(value) {}

		operator uint64() const
		{
			return Value;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const UHex64& nlohmann_json_t)
		{
			char buf[32];
			sprintf_s(buf, "0x%016llX", nlohmann_json_t.Value);
			nlohmann_json_j = std::string(buf);
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void from_json(const BasicJsonType& nlohmann_json_j, UHex64& nlohmann_json_t)
		{
			const UHex64 nlohmann_json_default_obj{};
			nlohmann_json_t.Value = !nlohmann_json_j.is_null()
				                        ? static_cast<uint64>(strtoull(nlohmann_json_j.template get<std::string>().c_str(), nullptr, 16))
				                        : nlohmann_json_default_obj.Value;
		}
	};

	struct UHex32
	{
		uint32 Value;

		UHex32() = default;

		UHex32(const uint32 value) :
			Value(value) {}

		operator uint32() const
		{
			return Value;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const UHex32& nlohmann_json_t)
		{
			char buf[16];
			sprintf_s(buf, "0x%08lX", nlohmann_json_t.Value);
			nlohmann_json_j = std::string(buf);
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void from_json(const BasicJsonType& nlohmann_json_j, UHex32& nlohmann_json_t)
		{
			const UHex32 nlohmann_json_default_obj{};
			nlohmann_json_t.Value = !nlohmann_json_j.is_null()
				                        ? static_cast<uint32>(strtoul(nlohmann_json_j.template get<std::string>().c_str(), nullptr, 16))
				                        : nlohmann_json_default_obj.Value;
		}
	};
}
