cmake_minimum_required(VERSION 3.28)
project(game)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
add_executable(game src/main.cpp
        src/Game.cpp
        src/Game.hpp
        src/Window.cpp
        src/Window.hpp
        src/gl.c
        src/Shader.cpp
        src/Shader.hpp
        src/VBO.cpp
        src/VBO.hpp
        src/VAO.cpp
        src/VAO.hpp
        src/ShaderProgram.cpp
        src/ShaderProgram.hpp
        src/EBO.cpp
        src/EBO.hpp
        src/Scene.hpp
        src/TestScene.hpp
        src/TestScene.hpp)
target_link_libraries(game glfw)