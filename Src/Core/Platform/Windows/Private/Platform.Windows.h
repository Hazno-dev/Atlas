// Hazno - 2026

#pragma once

#define WIN_USING(name) \
	using ::name

#define EXPORT_WIN_USING(name) \
	export WIN_USING(name)

#define EXPORT_WIN_MACRO_U32(name) \
	export inline constexpr uint32 SYS_##name = name

#define EXPORT_WIN_MACRO_S32(name) \
	export inline constexpr int32 SYS_##name = name

#define EXPORT_WIN_MACRO_PTR(name) \
	inline auto s_##name = name; \
	export inline constexpr auto SYS_##name = &s_##name

#define EXPORT_WIN_ENUM_EQUALITY(name, underlying_type) \
	export inline bool operator==(const underlying_type lhs, name rhs)								\
	{																								\
		return lhs == static_cast<underlying_type>(rhs);											\
	}																								\
	export inline bool operator!=(const underlying_type lhs, name rhs)								\
	{																								\
		return !(lhs == rhs);																		\
	}
