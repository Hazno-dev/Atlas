if("$ENV{VCPKG_ROOT}" STREQUAL "")
  message(FATAL_ERROR "VCPKG_ROOT is not set? Please check CMakePresets.json and ensure VCPKG_ROOT is pointing to external/vcpkg")
endif()

message(STATUS "Using vcpkg from: $ENV{VCPKG_ROOT}")
include($ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)