macro(exclude_files files exclusion)
    list(FILTER ${files} EXCLUDE REGEX ".*(\\/|\\\\)${exclusion}(\\/|\\\\).*")
endmacro()