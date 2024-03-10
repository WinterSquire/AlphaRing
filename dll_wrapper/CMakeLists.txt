cmake_minimum_required(VERSION 3.27)
project(dll_wrapper)

set(CMAKE_CXX_STANDARD 17)

set(WRAPPER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

FILE(GLOB_RECURSE WRAPPER_SRC ${WRAPPER_SRC_DIR}/*.h ${WRAPPER_SRC_DIR}/*.cpp)

add_compile_definitions(WRAPPER_DLL_NAME="${WRAPPER_DLL_NAME}")

# Use OBJECT To Export Symbol
add_library(dll_wrapper OBJECT ${WRAPPER_SRC})
