cmake_minimum_required(VERSION 3.27)
project(lib_halo3)

set(CMAKE_CXX_STANDARD 17)

include_directories(${COMMON_DIR}/include)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /Zi /O2 /Gr")

file(GLOB_RECURSE LIB_HALO3_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${LIB_HALO3_SRC})