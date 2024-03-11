project(lib_halo3)

file(GLOB_RECURSE LIB_HALO3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(lib_halo3 STATIC )