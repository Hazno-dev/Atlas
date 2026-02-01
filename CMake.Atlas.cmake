file(GLOB_RECURSE ATLAS_SOURCES_MODULES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.ixx")

file(GLOB_RECURSE ATLAS_SOURCES_IMPLS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cpp")

file(GLOB_RECURSE ATLAS_SOURCES_HEADERS CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.h")

list(FILTER ATLAS_SOURCES_HEADERS EXCLUDE REGEX ".*Src(\\/|\\\\)Precompiled(\\/|\\\\).*")

add_library(Atlas SHARED)
add_library(Atlas::Atlas ALIAS Atlas)

target_compile_features(Atlas
        PRIVATE   cxx_std_23
        INTERFACE cxx_std_20)

target_sources(Atlas
        PRIVATE
        ${ATLAS_SOURCES_IMPLS}
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES ${ATLAS_SOURCES_MODULES}
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES ${ATLAS_SOURCES_HEADERS})

target_include_directories(Atlas
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        ${VCPKG_IMPORT_PREFIX}/include)

find_package(fmt QUIET CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE fmt::fmt-header-only)

find_package(spdlog QUIET CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE spdlog::spdlog_header_only)

atlas_apply_target_base(Atlas)