cmake_minimum_required(VERSION 4.1.0)

add_executable(AtlasCodegen)

file(GLOB_RECURSE ATLAS_SOURCES_MODULES_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.ixx")
list(APPEND ATLAS_SOURCES_MODULES_CODEGEN ${ATLAS_SOURCES_MODULES})

file(GLOB_RECURSE ATLAS_SOURCES_IMPLS_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.cpp")
list(APPEND ATLAS_SOURCES_IMPLS_CODEGEN ${ATLAS_SOURCES_IMPLS})

file(GLOB_RECURSE ATLAS_SOURCES_HEADERS_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.h")
list(APPEND ATLAS_SOURCES_HEADERS_CODEGEN ${ATLAS_SOURCES_HEADERS})

target_compile_features(AtlasCodegen
        PRIVATE cxx_std_23
        INTERFACE cxx_std_20)

target_sources(AtlasCodegen
        PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES
        ${ATLAS_SOURCES_MODULES_CODEGEN}
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/"
        FILES
        ${ATLAS_SOURCES_HEADERS_CODEGEN}
        PRIVATE
        ${ATLAS_SOURCES_IMPLS_CODEGEN})

target_include_directories(AtlasCodegen
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
        PRIVATE
        ${VCPKG_IMPORT_PREFIX}/include)

find_package(fmt QUIET CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE fmt::fmt-header-only)

find_package(spdlog QUIET CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE spdlog::spdlog_header_only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE nlohmann_json::nlohmann_json)

find_package(inja CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE pantor::inja)

atlas_apply_target_base(AtlasCodegen)
atlas_add_resources(AtlasCodegen)