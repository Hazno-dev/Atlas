// Hazno - 2026

export module Common:Type;
import std;

#define DTL_EXPORT_ALIAS_W(alias)                                                           \
    DTL_EXPORT_ALIAS(alias, std :: alias##_t)

#define DTL_EXPORT_ALIAS(alias, type)                                                       \
    export using alias = type

#define DTL_EXPORT_ALIAS_CONVERT_W(type, prettyName)                                        \
    DTL_EXPORT_ALIAS_CONVERT(type, prettyName, std :: type##_t)

#define DTL_EXPORT_ALIAS_CONVERT(alias, prettyName, type)                                   \
    DTL_EXPORT_ALIAS(alias, type);                                                          \
    export template <typename ret, typename input>                                          \
        requires (InputConvertible<input>) && (OutputConvertible<ret, alias>)               \
    [[nodiscard]] ATLAS_FORCEINLINE constexpr ret To##prettyName(input v) noexcept          \
    {                                                                                       \
        using U = std::remove_cvref_t<input>;                                               \
        if constexpr (std::is_same_v<U, std::nullptr_t>) {                                  \
            if constexpr (std::is_pointer_v<ret>) {                                         \
                return nullptr;                                                             \
            } else {                                                                        \
                return ret{};                                                               \
            }                                                                               \
        } else if constexpr (std::is_pointer_v<U>) {                                        \
            if constexpr (std::is_pointer_v<ret>) {                                         \
                return reinterpret_cast<ret>(v);                                            \
            } else if constexpr (std::is_integral_v<ret>) {                                 \
                static_assert(sizeof(ret) >= sizeof(std::uintptr_t),                        \
                    ATLAS_STRING(prettyName) " is too small to hold a pointer.");           \
                return static_cast<alias>(v);                                               \
            } else {                                                                        \
                static_assert(sizeof(ret) >= sizeof(std::uintptr_t),                        \
                    ATLAS_STRING(prettyName) " is too small to hold a pointer.");           \
                return static_cast<ret>(reinterpret_cast<std::uintptr_t>(v));               \
            }                                                                               \
        } else {                                                                            \
            if constexpr (std::is_pointer_v<ret>) {                                         \
                return reinterpret_cast<ret>(static_cast<std::uintptr_t>(v));               \
            } else {                                                                        \
                return static_cast<ret>(v);                                                 \
            }                                                                               \
        }                                                                                   \
    }

template<typename input> concept InputConvertible =
    std::is_integral_v<std::remove_cvref_t<input>>
    || std::is_pointer_v<std::remove_cvref_t<input>>
    || std::is_same_v<std::remove_cvref_t<input>, std::nullptr_t>;

template<typename ret, typename alias> concept OutputConvertible =
    std::is_same_v<std::remove_cv_t<ret>, alias>
    || (std::is_pointer_v<ret> && std::is_same_v<std::remove_cv_t<std::remove_pointer_t<ret>>, alias>);

#define EXPORT_ALIAS(...)                                                                   \
    ATLAS_GET_MACRO_4(DTL_EXPORT_ALIAS_W, DTL_EXPORT_ALIAS, x, x, __VA_ARGS__)(__VA_ARGS__)
#define EXPORT_ALIAS_CONVERT(...)                                                           \
    ATLAS_GET_MACRO_4(x, DTL_EXPORT_ALIAS_CONVERT_W, DTL_EXPORT_ALIAS_CONVERT, x, __VA_ARGS__)(__VA_ARGS__)

//
// Basic types
//

EXPORT_ALIAS(ll,        long long);
EXPORT_ALIAS(ull,       unsigned long long);

EXPORT_ALIAS(uint,      unsigned int);
EXPORT_ALIAS(uchar,     unsigned char);
EXPORT_ALIAS(ushort,    unsigned short);
EXPORT_ALIAS(ulong,     unsigned long);

//
// Types w/ built-in conversions (i.e. ToUInt64)
//

EXPORT_ALIAS_CONVERT(int8,      Int8)
EXPORT_ALIAS_CONVERT(uint8,     UInt8)
EXPORT_ALIAS_CONVERT(int16,     Int16)
EXPORT_ALIAS_CONVERT(uint16,    UInt16)
EXPORT_ALIAS_CONVERT(int32,     Int32)
EXPORT_ALIAS_CONVERT(uint32,    UInt32)
EXPORT_ALIAS_CONVERT(int64,     Int64)
EXPORT_ALIAS_CONVERT(uint64,    UInt64)