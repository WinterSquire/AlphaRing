cmake_minimum_required(VERSION 3.27)
project(ring_core)

# set variables
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY_LIST dll_wrapper minhook imgui lua tinyxml2)

# include directory
include_directories(${IMGUI_DIR})
include_directories(${MINHOOK_DIR}/include)

add_library(${WRAPPER_NAME} SHARED main.cpp)

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})

install(TARGETS ${WRAPPER_NAME} DESTINATION ${MCC_DIR})
