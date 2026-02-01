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

#define DTL_ATLAS_IGNORE(x)
#define DTL_ATLAS_ID(x) x
#define DTL_ATLAS_STRING(x) #x
#define DTL_ATLAS_MERGE(x, y) x ## y
#define DTL_ATLAS_MERGE_WRAP(x, y) DTL_ATLAS_MERGE(x, y)

#define DTL_ATLAS_GET_MACRO_4(M4, M3, M2, M1, TARGET, ...) TARGET
