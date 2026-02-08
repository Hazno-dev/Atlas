cmake_minimum_required(VERSION 4.1.0)

add_library(Atlas SHARED)
add_library(Atlas::Atlas ALIAS Atlas)

target_compile_features(Atlas
        PRIVATE cxx_std_23
        INTERFACE cxx_std_20)

atlas_apply_base_sources(Atlas)

target_include_directories(Atlas
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        ${VCPKG_IMPORT_PREFIX}/include)

target_link_libraries(Atlas PRIVATE fmt::fmt)

find_package(spdlog QUIET CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE spdlog::spdlog_header_only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE nlohmann_json::nlohmann_json)

find_package(Boost REQUIRED QUIET COMPONENTS core mp11 describe)
target_link_libraries(Atlas PRIVATE ${Boost_LIBRARIES})

find_package(frozen CONFIG REQUIRED)
target_link_libraries(Atlas PRIVATE frozen::frozen frozen::frozen-headers)

atlas_apply_target_base(Atlas)
atlas_project_version(Atlas 1 0 0 0)