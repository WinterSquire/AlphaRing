cmake_minimum_required(VERSION 3.27)
project(ring_core)

# set variables
set(CMAKE_CXX_STANDARD 17)

# disable warning c4996
add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

set(LIBRARY_LIST
        common dll_wrapper directx11_hook
        minhook imgui lua spd_log tinyxml2
        Version
)

# include directory
include_directories(${IMGUI_DIR})
include_directories(${TINYXML2_DIR})
include_directories(${COMMON_DIR}/include)
include_directories(${MINHOOK_DIR}/include)
include_directories(${SPD_LOG_DIR}/include)
include_directories(${DIRECTX11_HOOK_DIR}/include)

add_compile_definitions(XML_NAME="data.xml")

file(GLOB_RECURSE CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${WRAPPER_NAME} SHARED ${CORE_SRC})

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})

install(TARGETS ${WRAPPER_NAME} DESTINATION ${MCC_DIR})
