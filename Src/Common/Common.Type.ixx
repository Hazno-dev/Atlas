// Hazno - 2026

module;

#include "Common/Private/Common.Macros.h"

export module Atlas.Common:Type;
import std;

//
// Basic types
//

EXPORT_ALIAS(ll, long long);
EXPORT_ALIAS(ull, unsigned long long);

EXPORT_ALIAS(uint, unsigned int);
EXPORT_ALIAS(uchar, unsigned char);
EXPORT_ALIAS(ushort, unsigned short);
EXPORT_ALIAS(ulong, unsigned long);

//
// Types w/ built-in conversions (i.e. ToUInt64)
//

EXPORT_ALIAS_CONVERT(int8, Int8);
EXPORT_ALIAS_CONVERT(uint8, UInt8);
EXPORT_ALIAS_CONVERT(int16, Int16);
EXPORT_ALIAS_CONVERT(uint16, UInt16);
EXPORT_ALIAS_CONVERT(int32, Int32);
EXPORT_ALIAS_CONVERT(uint32, UInt32);
EXPORT_ALIAS_CONVERT(int64, Int64);
EXPORT_ALIAS_CONVERT(uint64, UInt64);

//
// Concepts
//
EXPORT_CONCEPT(Cpt_Integral, (t_input), std::is_integral_v<std::remove_cv_t<t_input>>
               || std::is_pointer_v<std::remove_cv_t<t_input>>);

EXPORT_CONCEPT(Cpt_EnumIntegral, (t_input), std::is_enum_v<std::remove_const_t<t_input>>
               && std::is_integral_v<std::underlying_type_t<t_input>>);

EXPORT_CONCEPT(Cpt_Ptr, (t_input), std::is_pointer_v<std::remove_const_t<t_input>>);

EXPORT_CONCEPT(Cpt_C_W_Str, (t_input), std::is_same_v<t_input, const char*>
               || std::is_same_v<t_input, const wchar_t*>
               || std::is_same_v<t_input, nullptr_t>);
