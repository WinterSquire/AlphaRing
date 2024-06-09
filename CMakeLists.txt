cmake_minimum_required(VERSION 3.27)
project(alpha_ring)

set(CMAKE_CXX_STANDARD 17)

set(VERSION "1.3385.0.0")

set(WRAPPER_NAME "WTSAPI32")
set(WRAPPER_DLL_NAME "${WRAPPER_NAME}.dll")

set(LIBRARY_LIST
        libMinHook.x64 imgui lua spdlog tinyxml2
        Version
)

# disable warning c4996
add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

add_compile_definitions(WRAPPER_DLL_NAME="${WRAPPER_DLL_NAME}")
add_compile_definitions(GAME_VERSION="${VERSION}")

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/inc)
include_directories(${CMAKE_SOURCE_DIR}/inc/offset/${VERSION})

file(GLOB_RECURSE CORE_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(${WRAPPER_NAME} SHARED ${CORE_SRC})

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})
target_link_directories(${WRAPPER_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/lib/${CMAKE_BUILD_TYPE})

if (MSVC)
    target_link_options(${WRAPPER_NAME} PUBLIC /DEBUG)
else ()
    target_link_options(${WRAPPER_NAME} PUBLIC -g)
endif()

install(TARGETS ${WRAPPER_NAME} DESTINATION "${MCC_DIR}/mcc/binaries/win64")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/res/" DESTINATION "${MCC_DIR}/alpha_ring")
