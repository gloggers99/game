# <p style="text-align: center;">Game: OpenGL based 3D game framework</p>

## Why?

I wanted a game engine format like MonoGame or XNA, 
where game code and loops are written fully in code, 
for a more consistant and declarative approach. However 
modern 3D game engines do not provide a game "framework"
like interface, and are often locked behind 
commission and infamous start screens (Unity), 
so it made perfect sense to start an attempt to create a 
3D game "framework", without any bogus features or advertising built in.

## Getting Started:

### The Approach:
Similar to XNA/MonoGame, you are going to create your games COMPLETELY with code.
This means no fancy designer editor program like unity, no previewing, just straight
declarative consistant code.

### Writing your first scene:
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
at it bit by bit.