cmake_minimum_required(VERSION 3.16)
project(Engine)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_COMPILER_LAUNCHER ccache)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -march=native -pipe")

# Include directories
include_directories(
    glad/include
    include
    imgui
    imgui/backends
)

# Source files
set(SOURCES
    src/main.cpp
    include/stb_image.cpp
    glad/src/gl.c
    imgui/imgui.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/backends/imgui_impl_glfw.cpp
    imgui/backends/imgui_impl_opengl3.cpp
)

add_executable(Engine ${SOURCES})

# Link libraries
target_link_libraries(Engine
    glfw3
    opengl32
    gdi32
)