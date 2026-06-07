cmake_minimum_required(VERSION 4.1.0)

add_executable(AtlasCodegen)

file(GLOB_RECURSE ATLAS_SOURCES_MODULES_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.ixx")

file(GLOB_RECURSE ATLAS_SOURCES_IMPLS_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.cpp")

file(GLOB_RECURSE ATLAS_SOURCES_HEADERS_CODEGEN CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/*.h")

target_compile_features(AtlasCodegen
        PRIVATE cxx_std_23
        INTERFACE cxx_std_20)

atlas_apply_base_sources(AtlasCodegen)
target_sources(AtlasCodegen
        PUBLIC
        FILE_SET public_cxx_modules
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/"
        FILES
        ${ATLAS_SOURCES_MODULES_CODEGEN}
        FILE_SET public_headers
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/Codegen/"
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

target_link_libraries(AtlasCodegen PRIVATE fmt::fmt)

find_package(spdlog QUIET CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE spdlog::spdlog_header_only)

find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE nlohmann_json::nlohmann_json)

find_package(inja CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE pantor::inja)

find_package(Boost REQUIRED QUIET COMPONENTS core mp11 describe program_options)
target_link_libraries(AtlasCodegen PRIVATE ${Boost_LIBRARIES})

find_package(unofficial-vincentlaucsb-csv-parser CONFIG REQUIRED)
target_link_libraries(AtlasCodegen PRIVATE unofficial::vincentlaucsb-csv-parser::csv)

target_link_libraries(AtlasCodegen PRIVATE frozen::frozen)

find_path(FAST_CPP_CSV_PARSER_INCLUDE_DIRS "fast-cpp-csv-parser/csv.h")
target_include_directories(AtlasCodegen PRIVATE ${FAST_CPP_CSV_PARSER_INCLUDE_DIRS})


atlas_apply_target_base(AtlasCodegen)
atlas_add_resources(AtlasCodegen)
atlas_project_version(AtlasCodegen 1 0 0 0)
atlas_apply_output(AtlasCodegen)