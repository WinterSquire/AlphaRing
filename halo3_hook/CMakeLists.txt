project(halo3_hook)

enable_language(ASM_MASM)

file(GLOB_RECURSE HALO3_HOOK_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.asm ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

include_directories(${MINHOOK_DIR}/include)

add_library(${PROJECT_NAME} ${HALO3_HOOK_SRC})
