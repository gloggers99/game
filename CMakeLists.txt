cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
include_directories(imgui)
add_executable(game src/main.cpp
        src/Game.cpp
        src/Game.hpp
        src/Window.cpp
        src/Window.hpp
        src/gl.c
        src/shaders/Shader.cpp
        src/shaders/Shader.hpp
        src/vo/VBO.cpp
        src/vo/VBO.hpp
        src/vo/VAO.cpp
        src/vo/VAO.hpp
        src/shaders/ShaderProgram.cpp
        src/shaders/ShaderProgram.hpp
        src/vo/EBO.cpp
        src/vo/EBO.hpp
        src/Scene.hpp
        src/TestScene.hpp
        src/matrix/Camera.cpp
        src/matrix/Camera.hpp
        src/objects/Cube.cpp
        src/objects/Cube.hpp
        src/Texture.cpp
        src/Texture.hpp
        src/shaders/ShaderFactory.cpp
        src/shaders/ShaderFactory.hpp

        imgui/imgui.cpp
        imgui/imgui_demo.cpp
        imgui/imgui_draw.cpp
        imgui/imgui_widgets.cpp
        imgui/imgui_tables.cpp
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/imgui.h
)
target_link_libraries(game glfw)
