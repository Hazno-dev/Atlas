mark_as_advanced(CMAKE_TOOLCHAIN_FILE)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_compile_options(/Zc:preprocessor /Zi)

add_compile_definitions(_WINDOWS _WINSOCKAPI_ NOGDI _USRDLL SPDLOG_FMT_EXTERNAL FMT_IMPORT_STD FMT_MODULE=1)

message(STATUS "Current list dir: ${CMAKE_CURRENT_LIST_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/Vcpkg.cmake)