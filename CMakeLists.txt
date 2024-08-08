cmake_minimum_required(VERSION 3.27)
project(alpha_ring)

set(CMAKE_CXX_STANDARD 17)

set(VERSION "1.3385.0.0")

set(WRAPPER_NAME "WTSAPI32")
set(WRAPPER_DLL_NAME "${WRAPPER_NAME}.dll")

set(LIBRARY_LIST
        minhook imgui lua spdlog tinyxml2
        utils game
        Version
)

include_directories(${CMAKE_SOURCE_DIR}/src)

# json
include_directories(${CMAKE_SOURCE_DIR}/lib/json/include)

# imgui
add_library(imgui SHARED IMPORTED)
include_directories(${CMAKE_SOURCE_DIR}/lib/imgui/inc)
set_target_properties(imgui PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/imgui/lib/${CMAKE_BUILD_TYPE}/imgui.lib")

# lua
add_library(lua SHARED IMPORTED)
include_directories(${CMAKE_SOURCE_DIR}/lib/lua/inc)
set_target_properties(lua PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/lua/lib/${CMAKE_BUILD_TYPE}/lua.lib")

# spdlog
add_library(spdlog SHARED IMPORTED)
include_directories(${CMAKE_SOURCE_DIR}/lib/spdlog/inc)
set_target_properties(spdlog PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/spdlog/lib/${CMAKE_BUILD_TYPE}/spdlog.lib")

# tinyxml2
add_library(tinyxml2 SHARED IMPORTED)
include_directories(${CMAKE_SOURCE_DIR}/lib/tinyxml2/inc)
set_target_properties(tinyxml2 PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/tinyxml2/lib/${CMAKE_BUILD_TYPE}/tinyxml2.lib")

# minhook
add_library(minhook SHARED IMPORTED)
include_directories(${CMAKE_SOURCE_DIR}/lib/minhook/inc)
set_target_properties(minhook PROPERTIES IMPORTED_IMPLIB "${CMAKE_SOURCE_DIR}/lib/minhook/lib/${CMAKE_BUILD_TYPE}/libMinhook.x64.lib")

# utils
file(GLOB_RECURSE UTILS_SRC ${CMAKE_SOURCE_DIR}/lib/utils/src/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/lib/utils/inc)
add_library(utils ${UTILS_SRC})

# game
file(GLOB_RECURSE GAME_SRC ${CMAKE_SOURCE_DIR}/lib/game/src/*.cpp)
include_directories(${CMAKE_SOURCE_DIR}/lib/game/inc)
include_directories(${CMAKE_SOURCE_DIR}/lib/game/inc/${VERSION})
add_library(game ${GAME_SRC})

# disable warning c4996
add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)
add_definitions(-DIMGUI_DEFINE_MATH_OPERATORS)

add_compile_definitions(WRAPPER_DLL_NAME="${WRAPPER_DLL_NAME}")
add_compile_definitions(GAME_VERSION="${VERSION}")

file(GLOB_RECURSE CORE_SRC ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_library(${WRAPPER_NAME} SHARED ${CORE_SRC})

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})

if (MSVC)
    target_link_options(${WRAPPER_NAME} PUBLIC /DEBUG)
else ()
    target_link_options(${WRAPPER_NAME} PUBLIC -g)
endif()

install(TARGETS ${WRAPPER_NAME} DESTINATION "${MCC_DIR}/mcc/binaries/win64")
install(DIRECTORY "${CMAKE_SOURCE_DIR}/res/" DESTINATION "${MCC_DIR}/alpha_ring")
