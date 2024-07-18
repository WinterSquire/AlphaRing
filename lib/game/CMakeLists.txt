cmake_minimum_required(VERSION 3.27)
project(game)

set(VERSION "1.3385.0.0")
set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../utils/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc/${VERSION})

file(GLOB_RECURSE GAME_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(game ${GAME_SRC})
