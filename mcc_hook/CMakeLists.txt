cmake_minimum_required(VERSION 3.27)
project(mcc_hook)

enable_language(ASM_MASM)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE MCC_HOOK_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.asm" "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

include_directories(${MINHOOK_DIR}/include)

add_library(mcc_hook STATIC ${MCC_HOOK_SRC})
