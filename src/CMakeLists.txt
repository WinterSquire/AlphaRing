cmake_minimum_required(VERSION 3.27)
project(ring_core)

enable_language(ASM_MASM)

set(CMAKE_CXX_STANDARD 17)

# disable warning c4996
add_definitions(-D_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS)

# set variables
set(XML_NAME "data.xml")

set(WRAPPER_NAME "WTSAPI32")
set(WRAPPER_DLL_NAME "${WRAPPER_NAME}.dll")

set(MCC_DIR "E:\\SteamLibrary\\steamapps\\common\\Halo The Master Chief Collection\\mcc\\binaries\\win64")

set(LIBRARY_LIST
        minhook imgui lua spd_log tinyxml2
        Version
)

add_compile_definitions(XML_NAME="${XML_NAME}")
add_compile_definitions(WRAPPER_DLL_NAME="${WRAPPER_DLL_NAME}")

# include directory
include_directories(${IMGUI_DIR})
include_directories(${TINYXML2_DIR})
include_directories(${MINHOOK_DIR}/include)
include_directories(${SPD_LOG_DIR}/include)

include_directories(${CMAKE_SOURCE_DIR}/src)

file(GLOB_RECURSE CORE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/*.asm)

add_library(${WRAPPER_NAME} SHARED ${CORE_SRC})

target_link_libraries(${WRAPPER_NAME} PUBLIC ${LIBRARY_LIST})

install(TARGETS ${WRAPPER_NAME} DESTINATION ${MCC_DIR})
install(FILES ${CMAKE_SOURCE_DIR}/res/${XML_NAME} DESTINATION ${MCC_DIR})
