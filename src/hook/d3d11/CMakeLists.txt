cmake_minimum_required(VERSION 3.27)
project(directx11_hook)

set(CMAKE_CXX_STANDARD 17)

set(DIRECTX11_HOOK_SRC_DIR ../../../directx11_hook/src)

file(GLOB_RECURSE DIRECTX11_HOOK_SRC "${DIRECTX11_HOOK_SRC_DIR}/*.h" "${DIRECTX11_HOOK_SRC_DIR}/*.cpp")

include_directories(${IMGUI_DIR})
include_directories(${MINHOOK_DIR}/include)

add_library(directx11_hook STATIC ${DIRECTX11_HOOK_SRC})
