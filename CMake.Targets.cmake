# Module Partition/Interface Units - Any extensions to this should also be reflected in _HEADERS and _IMPLS
file(GLOB_RECURSE ATLAS_SOURCES_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Binding/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.ixx")

# Headers - Not really used since Atlas uses modules
file(GLOB_RECURSE ATLAS_SOURCES_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Binding/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.h")

exclude_files(ATLAS_SOURCES_HEADERS "Private")

# Impl - Implementation for both modules and headers
file(GLOB_RECURSE ATLAS_SOURCES_IMPLS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Binding/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.cpp")


set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

# Targets
include(CMake.Atlas.cmake)              #Main
include(CMake.Atlas.Codegen.cmake)      #Codegen Tool