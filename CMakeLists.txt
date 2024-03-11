cmake_minimum_required(VERSION 3.27)
project(alpha_ring)

set(CMAKE_CXX_STANDARD 17)

set(WRAPPER_NAME "WTSAPI32")
set(WRAPPER_DLL_NAME "${WRAPPER_NAME}.dll")

set(DIRECTX11_HOOK_DIR ${CMAKE_SOURCE_DIR}/directx11_hook)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/deps/imgui)
set(LUA_DIR ${CMAKE_SOURCE_DIR}/deps/lua)
set(MINHOOK_DIR ${CMAKE_SOURCE_DIR}/deps/minhook)
set(TINYXML2_DIR ${CMAKE_SOURCE_DIR}/deps/tinyxml2)

set(MCC_DIR "E:\\SteamLibrary\\steamapps\\common\\Halo The Master Chief Collection\\mcc\\binaries\\win64")

add_subdirectory(deps)
add_subdirectory(directx11_hook)
add_subdirectory(dll_wrapper)
add_subdirectory(ring_core)
