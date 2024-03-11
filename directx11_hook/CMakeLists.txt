project(directx11_hook)

set(DIRECTX11_HOOK_SRC)

set(DIRECTX11_HOOK_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE DIRECTX11_HOOK_SRC "${DIRECTX11_HOOK_SRC_DIR}/*.h" "${DIRECTX11_HOOK_SRC_DIR}/*.cpp")

include_directories(${IMGUI_DIR})
include_directories(${MINHOOK_DIR}/include)

add_library(directx11_hook STATIC ${DIRECTX11_HOOK_SRC})
