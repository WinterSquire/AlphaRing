project(common)

include_directories(${TINYXML2_DIR})

file(GLOB_RECURSE COMMON_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(${PROJECT_NAME} STATIC ${COMMON_SRC})
