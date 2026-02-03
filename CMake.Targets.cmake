file(GLOB_RECURSE ATLAS_SOURCES_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.ixx")

file(GLOB_RECURSE ATLAS_SOURCES_IMPLS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.cpp")

file(GLOB_RECURSE ATLAS_SOURCES_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.h")

exclude_files(ATLAS_SOURCES_HEADERS "Private")

include(CMake.Atlas.cmake)
include(CMake.Atlas.Codegen.cmake)
#include(CMake.AtlasStripped.cmake)