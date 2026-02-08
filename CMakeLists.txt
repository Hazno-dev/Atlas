cmake_minimum_required(VERSION 4.1.0)

set(ATLAS_DEFAULT_DEFINITIONS SPDLOG_FMT_EXTERNAL FROZEN_MODULE FROZEN_STD_MODULE FMT_IMPORT_STD FMT_MODULE FMT_ATTACH_TO_GLOBAL_MODULE)

project(Atlas VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CMake/Version.cmake)
include(CMake/Utility.cmake)
include(CMake/Precompile.cmake)
include(CMake/Resource.cmake)
include(CMake/Sources.cmake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CMake.Targets.cmake)
#[[

if (PROJECT_IS_TOP_LEVEL)
    install(TARGETS Atlas fmt
            EXPORT AtlasTargets
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            FILE_SET public_cxx_modules DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Atlas"
            FILE_SET public_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Atlas")

    install(EXPORT AtlasTargets
            NAMESPACE Atlas::
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas")

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfigVersion.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion)

    configure_package_config_file(
            "${CMAKE_CURRENT_SOURCE_DIR}/CMake/AtlasConfig.cmake.in"
            "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfig.cmake"
            INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas")

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfig.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfigVersion.cmake"
            DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas")
endif ()]]
