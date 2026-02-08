mark_as_advanced(CMAKE_TOOLCHAIN_FILE)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

add_compile_options(-w -ffunction-sections -fdata-sections -fbuiltin
        -fno-stack-protector -std=c++23 -fms-extensions)

add_compile_definitions(_WINDOWS _WIN32 _WINSOCKAPI_ NOGDI _USRDLL FMT_IMPORT_STD FMT_MODULE=1 FMT_ATTACH_TO_GLOBAL_MODULE
        SPDLOG_FMT_EXTERNAL WINVER=0x0601 _WIN32_WINNT=0x0601)

message(STATUS "Current list dir: ${CMAKE_CURRENT_LIST_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/Vcpkg.cmake)