project(lib_halo3)

file(GLOB_RECURSE LIB_HALO3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${COMMON_DIR}/include)

add_compile_definitions(XML_NAME="data.xml")

file(GLOB_RECURSE LIB_HALO3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_HALO3_SRC})