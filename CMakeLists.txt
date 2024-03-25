cmake_minimum_required(VERSION 3.27)
project(alpha_ring)

set(CMAKE_CXX_STANDARD 17)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
set(LUA_DIR ${CMAKE_SOURCE_DIR}/deps/lua)
set(MINHOOK_DIR ${CMAKE_SOURCE_DIR}/deps/minhook)
set(SPD_LOG_DIR ${CMAKE_SOURCE_DIR}/deps/spdlog)
set(TINYXML2_DIR ${CMAKE_SOURCE_DIR}/deps/tinyxml2)

add_subdirectory(deps)
add_subdirectory(src)
