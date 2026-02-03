cmake_minimum_required(VERSION 4.1.0)

project(Atlas VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMake/Utility.cmake)
include(CMake/Precompile.cmake)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CMake.Targets.cmake)

if (PROJECT_IS_TOP_LEVEL)
    install(TARGETS Atlas
            EXPORT AtlasTargets
            ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
            FILE_SET CXX_MODULES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Atlas"
            FILE_SET HEADERS DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Atlas")

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
endif ()