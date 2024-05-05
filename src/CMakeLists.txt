cmake_minimum_required(VERSION 3.27)
project(ring_core)

set(CMAKE_CXX_STANDARD 17)

set(VERSION "1.3385.0.0")

set(WRAPPER_NAME "WTSAPI32")
set(WRAPPER_DLL_NAME "${WRAPPER_NAME}.dll")

set(LIBRARY_LIST
        minhook imgui lua spd_log tinyxml2
        Version
)

# disable warning c4996
add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

add_compile_definitions(WRAPPER_DLL_NAME="${WRAPPER_DLL_NAME}")
add_compile_definitions(GAME_VERSION="${VERSION}")

# include directory
include_directories(${IMGUI_DIR})
include_directories(${TINYXML2_DIR})
include_directories(${MINHOOK_DIR}/include)
include_directories(${SPD_LOG_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/inc/offset/${VERSION})

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${WRAPPER_NAME} SHARED ${CORE_SRC}
        module/Module.cpp
        module/Module.h
        imgui/home_page.cpp
        imgui/home_page.h)

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})

install(TARGETS ${WRAPPER_NAME} DESTINATION "${MCC_DIR}/mcc/binaries/win64")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/res/" DESTINATION "${MCC_DIR}/alpha_ring")
