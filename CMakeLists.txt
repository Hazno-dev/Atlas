cmake_minimum_required(VERSION 3.28)
project(Atlas VERSION 0.1.0 LANGUAGES CXX)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CMake/Scaffold.cmake)

file(GLOB_RECURSE ATLAS_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/*.cppm")

# Stripping
file(GLOB_RECURSE ATLAS_SOURCES_STRIPPED CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.ixx"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.cppm")
list(FILTER ATLAS_SOURCES_STRIPPED EXCLUDE REGEX ".*\\.Gen\\.(ixx|cppm)$")
list(FILTER ATLAS_SOURCES_STRIPPED EXCLUDE REGEX ".*(\\/|\\\\)Impl(\\/|\\\\).*")


# Lib
scaffold_target(Atlas Atlas "${CMAKE_CURRENT_SOURCE_DIR}/Src/" ${ATLAS_SOURCES})
target_include_directories(Atlas PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/Src>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

scaffold_target(AtlasStripped Stripped "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game" ${ATLAS_SOURCES_STRIPPED})

install(TARGETS Atlas AtlasStripped
        EXPORT AtlasTargets
        ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        FILE_SET CXX_MODULES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/Atlas"
)

install(EXPORT AtlasTargets
        NAMESPACE Atlas::
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas"
)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/CMake/AtlasConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfig.cmake"
        INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas"
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/AtlasConfigVersion.cmake"
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/CMake/Atlas"
)