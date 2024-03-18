project(lib_halo3)

include_directories(${COMMON_DIR}/include)

file(GLOB_RECURSE LIB_HALO3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_HALO3_SRC})