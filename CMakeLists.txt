cmake_minimum_required(VERSION 3.12)

project(alpha_ring VERSION 1.0.0 LANGUAGES CXX)

find_package(libmcc REQUIRED)

add_compile_definitions(UNICODE)
set(CMAKE_CXX_STANDARD 20)

set(SRC 
	"src/input.cpp"
	"src/player_customization.cpp"
	"src/string_table.cpp"
	"src/main.cpp"
	"src/mcc.cpp" 
	"src/player.cpp" 
	"src/rasterizer.cpp" 
	"src/render.cpp" 
	"src/win32helper.cpp"
)

set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/dep/imgui)

set(IMGUI_SRC 
	${IMGUI_DIR}/imgui.cpp
	${IMGUI_DIR}/imgui_demo.cpp
	${IMGUI_DIR}/imgui_draw.cpp
	${IMGUI_DIR}/imgui_tables.cpp
	${IMGUI_DIR}/imgui_widgets.cpp
	${IMGUI_DIR}/backends/imgui_impl_win32.cpp
	${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

project(imgui)
add_library(imgui STATIC ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${IMGUI_DIR})

set(LIB 
	libmcc::libmcc
	d3d11 xinput imgui
)

project(WTSAPI32)
add_library(${PROJECT_NAME} SHARED ${SRC} "src/main.dll.cpp")
target_link_libraries(${PROJECT_NAME} ${LIB})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)

project(test)
add_executable(${PROJECT_NAME} ${SRC})
target_link_libraries(${PROJECT_NAME} ${LIB})
target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS")
