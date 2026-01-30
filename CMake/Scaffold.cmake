macro(scaffold_target name alias base_dirs sources)
    add_library(${name} STATIC)
    add_library(Atlas::${alias} ALIAS ${name})

    target_compile_features(${name} PUBLIC cxx_std_20)

    target_sources(${name} PUBLIC
            FILE_SET CXX_MODULES
            BASE_DIRS ${base_dirs}
            FILES ${sources}
    )
endmacro()