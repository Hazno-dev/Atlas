// Hazno - 2026

// ReSharper disable CppInconsistentNaming
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

EXPORT_CONCEPT(Cpt_UIntegral, (t_input), Cpt_Integral<t_input> && std::is_unsigned_v<t_input>);
EXPORT_CONCEPT(Cpt_Integral32, (t_input), Cpt_Integral<t_input> && sizeof(t_input) == 4);
EXPORT_CONCEPT(Cpt_Integral64, (t_input), Cpt_Integral<t_input> && sizeof(t_input) >= 8);
EXPORT_CONCEPT(Cpt_UIntegral32, (t_input), Cpt_UIntegral<t_input> && sizeof(t_input) == 4);
EXPORT_CONCEPT(Cpt_UIntegral64, (t_input), Cpt_UIntegral<t_input> && sizeof(t_input) >= 8);

EXPORT_CONCEPT(Cpt_EnumIntegral, (t_input), std::is_enum_v<std::remove_const_t<t_input>>
               && std::is_integral_v<std::underlying_type_t<t_input>>);

EXPORT_CONCEPT(Cpt_Ptr, (t_input), std::is_pointer_v<std::remove_const_t<t_input>>);
EXPORT_CONCEPT(Cpt_Null, (t_input), std::is_same_v<t_input, nullptr_t>);

EXPORT_CONCEPT(Cpt_CStr, (t_input), std::is_same_v<t_input, const char*> || Cpt_Null<t_input>);
EXPORT_CONCEPT(Cpt_WStr, (t_input), std::is_same_v<t_input, const wchar_t*> || Cpt_Null<t_input>);
EXPORT_CONCEPT(Cpt_C_W_Str, (t_input), Cpt_CStr<t_input> || Cpt_WStr<t_input>);
