project(deps)

# setup minhook
file(GLOB_RECURSE SRC_MINHOOK "${CMAKE_CURRENT_SOURCE_DIR}/minhook/src/*.c")

add_compile_definitions(IM_ASSERT="((void)(_EXPR))") # disable assert

add_library(minhook STATIC ${SRC_MINHOOK})

# setup imgui
include_directories(${IMGUI_DIR})

set(SRC_IMGUI
        ${IMGUI_DIR}/imgui.h
        ${IMGUI_DIR}/imconfig.h
        ${IMGUI_DIR}/imstb_rectpack.h
        ${IMGUI_DIR}/imstb_textedit.h
        ${IMGUI_DIR}/imstb_truetype.h
        ${IMGUI_DIR}/imgui_internal.h
        ${IMGUI_DIR}/backends/imgui_impl_win32.h
        ${IMGUI_DIR}/backends/imgui_impl_dx11.h

        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_win32.cpp
        ${IMGUI_DIR}/backends/imgui_impl_dx11.cpp
)

add_library(imgui STATIC ${SRC_IMGUI})

# setup lua
include_directories(${LUA_DIR})

set (LUA_SRC
        ${LUA_DIR}/lapi.c
        ${LUA_DIR}/lcode.c
        ${LUA_DIR}/lctype.c
        ${LUA_DIR}/ldebug.c
        ${LUA_DIR}/ldo.c
        ${LUA_DIR}/ldump.c
        ${LUA_DIR}/lfunc.c
        ${LUA_DIR}/lgc.c
        ${LUA_DIR}/llex.c
        ${LUA_DIR}/lmem.c
        ${LUA_DIR}/lobject.c
        ${LUA_DIR}/lopcodes.c
        ${LUA_DIR}/lparser.c
        ${LUA_DIR}/lstate.c
        ${LUA_DIR}/lstring.c
        ${LUA_DIR}/ltable.c
        ${LUA_DIR}/ltm.c
        ${LUA_DIR}/lundump.c
        ${LUA_DIR}/lvm.c
        ${LUA_DIR}/lzio.c
        ${LUA_DIR}/lauxlib.c
        ${LUA_DIR}/lbaselib.c
        ${LUA_DIR}/lcorolib.c
        ${LUA_DIR}/ldblib.c
        ${LUA_DIR}/liolib.c
        ${LUA_DIR}/lmathlib.c
        ${LUA_DIR}/loslib.c
        ${LUA_DIR}/lstrlib.c
        ${LUA_DIR}/ltablib.c
        ${LUA_DIR}/lutf8lib.c
        ${LUA_DIR}/loadlib.c
        ${LUA_DIR}/linit.c
)

add_library(lua STATIC ${LUA_SRC} )

# setup spdlog
include_directories(${SPD_LOG_DIR}/include)

file(GLOB_RECURSE SPD_LOG_SRC "${SPD_LOG_DIR}/src/*.cpp")

add_definitions(-DSPDLOG_COMPILED_LIB)

add_library(spd_log STATIC ${SPD_LOG_SRC})

# setup tinyxml2
include_directories(${TINYXML2_DIR})

add_library(tinyxml2 STATIC ${TINYXML2_DIR}/tinyxml2.cpp)