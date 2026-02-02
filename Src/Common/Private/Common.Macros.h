// Hazno - 2026

#pragma once

#include <type_traits>

#define DTL_EXPORT_ALIAS_W(alias)                                                           \
    DTL_EXPORT_ALIAS(alias, std :: alias##_t)

#define DTL_EXPORT_ALIAS(alias, type)                                                       \
    export using alias = type

#define DTL_EXPORT_ALIAS_CONVERT_W(type, prettyName)                                        \
    DTL_EXPORT_ALIAS_CONVERT(type, prettyName, std :: type##_t)

#define DTL_EXPORT_ALIAS_CONVERT(alias, prettyName, type)                                   \
    DTL_EXPORT_ALIAS(alias, type);                                                          \
    export template <typename ret = alias, typename input>                                  \
        requires (InputConvertible<input>) && (OutputConvertible<ret, alias>)               \
    [[nodiscard]] ATLAS_FORCE_INLINE constexpr ret To##prettyName(input v) noexcept         \
    {                                                                                       \
        using U = std::remove_cvref_t<input>;                                               \
		if constexpr (std::is_convertible_v<U, ret>) {                                      \
			return static_cast<ret>(v);														\
		}																					\
		else if constexpr (std::is_same_v<U, std::nullptr_t>) {                             \
            if constexpr (std::is_pointer_v<ret>) {                                         \
                return nullptr;                                                             \
            } else {                                                                        \
                return ret{};                                                               \
            }                                                                               \
        } else if constexpr (std::is_pointer_v<U>) {										\
			static_assert(sizeof(ret) >= sizeof(std::uintptr_t),							\
				ATLAS_STRING(prettyName) " is too small to hold a pointer.");				\
            if constexpr (std::is_pointer_v<ret>) {                                         \
                return reinterpret_cast<ret>(v);                                            \
            } else {                                                                        \
                static_assert(sizeof(ret) >= sizeof(std::uintptr_t),                        \
                    ATLAS_STRING(prettyName) " is too small to hold a pointer.");           \
                return static_cast<ret>(reinterpret_cast<std::uintptr_t>(v));               \
            }                                                                               \
        } else {                                                                            \
			reinterpret_cast<ret>(v);														\
        }                                                                                   \
    }

template <typename t_input> concept InputConvertible =
		std::is_integral_v<std::remove_cvref_t<t_input>>
		|| std::is_pointer_v<std::remove_cvref_t<t_input>>
		|| std::is_same_v<std::remove_cvref_t<t_input>, std::nullptr_t>;

template <typename t_ret, typename t_alias> concept OutputConvertible =
		std::is_same_v<std::remove_cv_t<t_ret>, t_alias>
		|| (std::is_pointer_v<t_ret> && std::is_same_v<std::remove_cv_t<std::remove_pointer_t<t_ret>>, t_alias>);

#define EXPORT_ALIAS(...)                                                                   \
    ATLAS_GET_MACRO_4(DTL_EXPORT_ALIAS_W, DTL_EXPORT_ALIAS, x, x, __VA_ARGS__)(__VA_ARGS__)
#define EXPORT_ALIAS_CONVERT(...)                                                           \
    ATLAS_GET_MACRO_4(x, DTL_EXPORT_ALIAS_CONVERT_W, DTL_EXPORT_ALIAS_CONVERT, x, __VA_ARGS__)(__VA_ARGS__)

#define EXPORT_CONCEPT(name, types, ...)													\
	export template<ATLAS_UNPARENS(types)> concept name = __VA_ARGS__;
