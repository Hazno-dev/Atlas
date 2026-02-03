cmake_minimum_required(VERSION 4.1.0)

add_library(Atlas SHARED)
add_library(Atlas::Atlas ALIAS Atlas)

target_compile_features(Atlas
        PRIVATE cxx_std_23
        INTERFACE cxx_std_20)

target_sources(Atlas
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES
        ${ATLAS_SOURCES_MODULES}
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES
        ${ATLAS_SOURCES_HEADERS}
        PRIVATE
        ${ATLAS_SOURCES_IMPLS})

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

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE nlohmann_json::nlohmann_json)

atlas_apply_target_base(Atlas)