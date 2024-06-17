# Game: OpenGL based 3D game framework

<!--toc:start-->
- [Game: OpenGL based 3D game framework](#game-opengl-based-3d-game-framework)
  - [Why?](#why)
  - [Getting Started](#getting-started)
    - [The Approach](#the-approach)
    - [Writing your first scene](#writing-your-first-scene)
  - [Basics](#basics)
    - [Drawing a cube](#drawing-a-cube)
<!--toc:end-->

## Why?

I wanted a game engine format like MonoGame or XNA, 
where game code and loops are written fully in code, 
for a more consistant and declarative approach. However 
modern 3D game engines do not provide a game "framework"
like interface, and are often locked behind 
commission and infamous start screens (Unity), 
so it made perfect sense to start an attempt to create a 
3D game "framework", without any bogus features or advertising built in.

## Getting Started

### The Approach
Similar to XNA/MonoGame, you are going to create your games COMPLETELY with code.
This means no fancy designer editor program like unity, no previewing, just straight
declarative consistant code.

### Writing your first scene
Let's begin by creating a Scene. Create a class with the name of your choice, 
I will be using `TestScene.hpp`, This is not a C++ tutorial, so basic knowledge 
of C++ will be needed.

```c++
#pragma once

#include "/path/to/Scene.hpp"

class TestScene : public Scene {
protected:
    void init() override {
        /*
            this is where you will initialize all of your
            classwide variables, or run any initialization
            code needed.
        */
    }
    void loop() override {
        /*
            this is your scene render loop, it is ran in a
            cycle until this->end() is ran, or the window
            is closed.
        */
    }
};
```

The scene class is simply a blueprint for the game engine to execute. The following
is some basic opengl rendering code to simply change the color.

```c++
#pragma once

#include "/path/to/Scene.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class TestScene : public Scene {
protected:
    void init() override {}
    void loop() override {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        
        /*
            some game variables are pre provided in the class,
            this->game is a pointer to the Game.hpp class,
            this->window is a pointer to the Window.hpp class
        */
        this->window->swapBuffers();
    }
};
```

Rendering using opengl is out of the scope of this tutorial, the goal is to abstract
most of opengl's functionality into classes throughout Game, however im still working
at it bit by bit. However a glfw and opengl environment is provided for you to work with,
and advanced users can utilize the full opengl toolset with a simplified Scene like structure.

## Basics

### Drawing a cube

```c++
#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "Texture.hpp"
#include "matrix/Camera.hpp"
#include "objects/Cube.hpp"

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class TestScene : public Scene {
    private:
        Camera camera = Camera();

        Cube *cube;

    protected:
        void init() override {
            /* 
                first we have to initialize our cube object,
                supplying it with a shader program to use.
                This is subject to change.
            */
            this->cube = new Cube(*this->defaultShaderProgram);
        }

        void loop(float deltaTime) override {
            /*
                clear the screen and depth buffer and draw 
                a basic background color.
            */
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            /*
                load the camera's projection and view matrix,
                this is subject to change and be simplified.
            */
            this->defaultShaderProgram->use();
            this->defaultShaderProgram->modifyUniform("projection", this->camera.createProjectionMatrix(this->window));
            this->defaultShaderProgram->modifyUniform("view", camera.createViewMatrix());

            /*
                finally draw our cube.
            */
            this->cube->draw();

            this->window->swapBuffers();
        }

};

#endif //GAME_TESTSCENE_HPP
```
