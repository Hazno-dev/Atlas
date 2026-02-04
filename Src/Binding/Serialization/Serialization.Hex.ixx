// Hazno - 2026

module;

#include <nlohmann/json.hpp>

export module Atlas.Binding.Serialization:Hex;
import Atlas.Common;
import std;

namespace Atlas::Binding
{
	struct Data_UHex64
	{
		uint64 Value;

		Data_UHex64() = default;

		Data_UHex64(const uint64 value) :
			Value(value) {}

		operator uint64() const
		{
			return Value;
		}

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
		}
	};

	struct Data_UHex32
	{
		uint32 Value;

		Data_UHex32() = default;

		Data_UHex32(const uint32 value) :
			Value(value) {}

		operator uint32() const
		{
			return Value;
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<
			          nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void to_json(BasicJsonType& nlohmann_json_j, const Data_UHex32& nlohmann_json_t)
		{
			char buf[16];
			sprintf_s(buf, "%X", nlohmann_json_t.Value);
			nlohmann_json_j = std::string(buf);
		}

		template <typename BasicJsonType, nlohmann::detail::enable_if_t<
			          nlohmann::detail::is_basic_json<BasicJsonType>::value, int> = 0>
		friend void from_json(const BasicJsonType& nlohmann_json_j, Data_UHex32& nlohmann_json_t)
		{
			const Data_UHex32 nlohmann_json_default_obj{};
			nlohmann_json_t.Value = !nlohmann_json_j.is_null()
				                        ? static_cast<uint32>(strtoul(nlohmann_json_j.template get<std::string>().c_str(), nullptr, 16))
				                        : nlohmann_json_default_obj.Value;
		}
	};
}
