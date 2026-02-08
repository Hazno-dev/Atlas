macro(atlas_exclude_files files exclusion)
    list(FILTER ${files} EXCLUDE REGEX ".*(\\/|\\\\)${exclusion}(\\/|\\\\).*")
endmacro()

macro(atlas_apply_output Target)
    set_target_properties(${Target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${Target}"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${Target}"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${Target}"
            PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/${Target}"
    )
endmacro()