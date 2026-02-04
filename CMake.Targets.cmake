# Module Partition/Interface Units - Any extensions to this should also be reflected in _HEADERS and _IMPLS
file(GLOB_RECURSE ATLAS_SOURCES_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.ixx")

# Headers - Not really used since Atlas uses modules
file(GLOB_RECURSE ATLAS_SOURCES_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.h")

exclude_files(ATLAS_SOURCES_HEADERS "Private")

# Impl - Implementation for both modules and headers
file(GLOB_RECURSE ATLAS_SOURCES_IMPLS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.cpp")


# Targets
include(CMake.Atlas.cmake)              #Main
include(CMake.Atlas.Codegen.cmake)      #Codegen Tool