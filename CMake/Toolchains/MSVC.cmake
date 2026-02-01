mark_as_advanced(CMAKE_TOOLCHAIN_FILE)

add_compile_options(/Zc:preprocessor)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

message(STATUS "Current list dir: ${CMAKE_CURRENT_LIST_DIR}")
include(${CMAKE_CURRENT_LIST_DIR}/Vcpkg.cmake)