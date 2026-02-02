// Hazno - 2026

#pragma once

/*
 * !! Header is precompiled !!
 * Anything defined here will be visible in all Atlas compilation units.
 *
 * ANY MUTATIONS WILL REQUIRE A FULL RECOMPILATION
 */

/*
 * Convert a macro argument to a string
 *
 * Example
 * "Hello" ATLAS_STRING(Something) "world";
 */
#define ATLAS_STRING(x) DTL_ATLAS_STRING(x)

/*
 * Define a padding array of specified size
 *
 * Example
 * ATLAS_PADDING(0x10);
 */
#define ATLAS_PADDING(size) uint8 DTL_ATLAS_MERGE_WRAP(pad, __COUNTER__)[size]

#define ATLAS_FOR_EACH(macro, ...) DTL_ATLAS_FOR_EACH(macro, __VA_ARGS__)

#define ATLAS_UNPARENS(args) DTL_ATLAS_UNPARENS(args)

/*
 * Define a stub function returning specified type
 *
 * Example
 * ATLAS_STUB_R(bool (return value), int64 param1, char* param2);
 */
#define ATLAS_STUB_RETURN(ret, ...) ret DTL_ATLAS_MERGE_WRAP(funcStub, __COUNTER__)(__VA_ARGS__) = 0

/*
 * Define a stub virtual function returning int64
 *
 * Example
 * ATLAS_STUB(int64 param1, char* param2);
 */
#define ATLAS_STUB(...) ATLAS_STUB_RETURN(virtual int64, __VA_ARGS__)

/*
 * Validate size of a type at compile time
 *
 * Example
 * ATLAS_VALIDATE_SIZE(MyStruct, 0x20);
 */
#define ATLAS_VALIDATE_SIZE(type, size) static_assert(sizeof(type) == size, "Invalid size for " #type)

/*
 * Select a macro based on number of arguments (4)
 *
 * Example
 * #define MACRO(...) ATLAS_GET_MACRO_4(Macro1, Macro2, Macro3, Macro4, __VA_ARGS__)(__VA_ARGS__)
 */
#define ATLAS_GET_MACRO_4(M1, M2, M3, M4, ...) DTL_ATLAS_GET_MACRO_4(__VA_ARGS__, M4, M3, M2, M1, FILLER)


//
//Detail macros. Not intended for direct use
//

//Util

#define DTL_ATLAS_PARENS ()
#define DTL_ATLAS_EMPTY(x)
#define DTL_ATLAS_EXPAND(x) x
#define DTL_ATLAS_STRING(x) #x
#define DTL_ATLAS_MERGE(x, y) x ## y
#define DTL_ATLAS_MERGE_WRAP(x, y) DTL_ATLAS_MERGE(x, y)

//Macro getter impl

#define DTL_ATLAS_GET_MACRO_4(M4, M3, M2, M1, TARGET, ...) TARGET

//Foreach impl
//From https://www.scs.stanford.edu/~dm/blog/va-opt.html

#define DTL_ATLAS_EXPAND0(...) DTL_ATLAS_EXPAND4(DTL_ATLAS_EXPAND4(DTL_ATLAS_EXPAND4(DTL_ATLAS_EXPAND4(__VA_ARGS__))))
#define DTL_ATLAS_EXPAND4(...) DTL_ATLAS_EXPAND3(DTL_ATLAS_EXPAND3(DTL_ATLAS_EXPAND3(DTL_ATLAS_EXPAND3(__VA_ARGS__))))
#define DTL_ATLAS_EXPAND3(...) DTL_ATLAS_EXPAND2(DTL_ATLAS_EXPAND2(DTL_ATLAS_EXPAND2(DTL_ATLAS_EXPAND2(__VA_ARGS__))))
#define DTL_ATLAS_EXPAND2(...) DTL_ATLAS_EXPAND1(DTL_ATLAS_EXPAND1(DTL_ATLAS_EXPAND1(DTL_ATLAS_EXPAND1(__VA_ARGS__))))
#define DTL_ATLAS_EXPAND1(...) __VA_ARGS__

#define DTL_ATLAS_FOR_EACH(macro, ...)										\
	__VA_OPT__(DTL_ATLAS_EXPAND0(DTL_ATLAS_FOR_EACH_HELPER(macro, __VA_ARGS__)))

#define DTL_ATLAS_FOR_EACH_HELPER(macro, a1, ...)								\
	macro a1														\
	__VA_OPT__(, DTL_ATLAS_FOR_EACH_AGAIN DTL_ATLAS_PARENS (macro, __VA_ARGS__))

#define DTL_ATLAS_FOR_EACH_AGAIN() DTL_ATLAS_FOR_EACH_HELPER

//Unparent impl
//From https://stackoverflow.com/a/46311121

#define DTL_ATLAS_REALLY_UNPARENS(...) ATLAS_FOR_EACH(typename , __VA_ARGS__)
#define DTL_ATLAS_UNPARENS(args) DTL_ATLAS_EXPAND(DTL_ATLAS_REALLY_UNPARENS args)
