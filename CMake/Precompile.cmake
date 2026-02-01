set(ATLAS_PRECOMPILED_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Precompiled/Definitions.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Precompiled/Macros.h")

string(TOUPPER "ATLAS_PLATFORM_${CMAKE_CXX_COMPILER_ID}" ATLAS_PLATFORM_DEF)

macro(atlas_apply_target_base Target)
    target_precompile_headers(${Target}
            PRIVATE
            ${ATLAS_PRECOMPILED_HEADERS})

    target_compile_definitions(${Target}
            PRIVATE
            ${ATLAS_PLATFORM_DEF})
endmacro()