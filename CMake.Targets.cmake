set(Boost_USE_STATIC_LIBS ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON)  # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

set(FMT_MODULE ON)
add_subdirectory(External/fmt EXCLUDE_FROM_ALL)
add_subdirectory(External/frozen EXCLUDE_FROM_ALL)

# Targets
include(CMake.Atlas.cmake)              #Main
include(CMake.Atlas.Codegen.cmake)      #Codegen Tool