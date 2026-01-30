file(GLOB_RECURSE ATLAS_SOURCES_STRIPPED CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game/*.ixx")

list(FILTER ATLAS_SOURCES_STRIPPED EXCLUDE REGEX ".*\\.Gen\\.(ixx)$")
list(FILTER ATLAS_SOURCES_STRIPPED EXCLUDE REGEX ".*(\\/|\\\\).Impl(\\/|\\\\).*")

add_library(AtlasStripped STATIC)
add_library(Atlas::Stripped ALIAS AtlasStripped)

target_compile_features(AtlasStripped PUBLIC cxx_std_20)

target_sources(AtlasStripped PUBLIC
        FILE_SET CXX_MODULES
        BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game"
        FILES ${ATLAS_SOURCES_STRIPPED})