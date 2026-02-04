# All Resources - These are available to all targets (duh)
file(GLOB_RECURSE ATLAS_SOURCES_RESOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources/All/*")

find_package(CMakeRC CONFIG REQUIRED)
cmrc_add_resource_library(AtlasResources
        ALIAS Atlas::Resources
        WHENCE "${CMAKE_CURRENT_SOURCE_DIR}/Resources/All"
        NAMESPACE Atlas::Resources
        ${ATLAS_SOURCES_RESOURCES})

function(atlas_add_resources Target)
    file(GLOB_RECURSE ${TARGET}_RESOURCES CONFIGURE_DEPENDS
            "${CMAKE_CURRENT_SOURCE_DIR}/Resources/${Target}/*")


    cmrc_add_resources(AtlasResources
            WHENCE "${CMAKE_CURRENT_SOURCE_DIR}/Resources/${Target}"
            ${${TARGET}_RESOURCES})

    target_link_libraries(${Target} PRIVATE Atlas::Resources)
endfunction()
