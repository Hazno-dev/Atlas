set(ATLAS_BASE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Common"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Binding"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Core"
        "${CMAKE_CURRENT_SOURCE_DIR}/Src/Game")

macro(atlas_collect_base_files Var Expression)
    foreach (Dir IN LISTS ATLAS_BASE_SOURCES)
        file(GLOB_RECURSE Temp CONFIGURE_DEPENDS
                "${Dir}/${Expression}")
        list(APPEND ${Var} ${Temp})
    endforeach ()
endmacro()

# Module Partition/Interface Units - Any extensions to this should also be reflected in _HEADERS and _IMPLS
atlas_collect_base_files(ATLAS_SOURCES_MODULES "*.ixx")
exclude_files(ATLAS_SOURCES_MODULES "Private")

atlas_collect_base_files(ATLAS_SOURCES_MODULES_PRIVATE "*/Private/*.ixx")
atlas_collect_base_files(ATLAS_SOURCES_MODULES_PRIVATE "/Private/*.ixx")

# Headers - Not really used since Atlas uses modules
atlas_collect_base_files(ATLAS_SOURCES_HEADERS "*.h")
exclude_files(ATLAS_SOURCES_HEADERS "Private")

atlas_collect_base_files(ATLAS_SOURCES_HEADERS_PRIVATE "*/Private/*.h")
atlas_collect_base_files(ATLAS_SOURCES_HEADERS_PRIVATE "/Private/*.h")

# Impl - Implementation for both modules and headers
atlas_collect_base_files(ATLAS_SOURCES_IMPLS "*.cpp")

function(atlas_apply_base_sources Target)
    target_sources(${Target}
            PUBLIC
            FILE_SET public_cxx_modules
            TYPE CXX_MODULES
            BASE_DIRS ${ATLAS_BASE_SOURCES}
            FILES ${ATLAS_SOURCES_MODULES}
            FILE_SET public_headers
            TYPE HEADERS
            BASE_DIRS ${ATLAS_BASE_SOURCES}
            FILES ${ATLAS_SOURCES_HEADERS})
    target_sources(${Target}
            PRIVATE
            FILE_SET private_cxx_modules
            TYPE CXX_MODULES
            BASE_DIRS ${ATLAS_BASE_SOURCES}
            FILES ${ATLAS_SOURCES_MODULES_PRIVATE}
            FILE_SET private_headers
            TYPE HEADERS
            BASE_DIRS ${ATLAS_BASE_SOURCES}
            FILES ${ATLAS_SOURCES_HEADERS_PRIVATE})
    target_sources(${Target}
            PRIVATE
            ${ATLAS_SOURCES_IMPLS})

    message("private ixx: ${ATLAS_SOURCES_MODULES_PRIVATE}")
    message("private headers: ${ATLAS_SOURCES_HEADERS_PRIVATE}")
endfunction()