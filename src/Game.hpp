//
// Created by lucas on 6/10/24.
//

#ifndef GAME_GAME_HPP
#define GAME_GAME_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "Window.hpp"

class Scene;

class Game {
private:
    static void error_callback(int error, const char *description);
    static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

    Window *window;
public:
    void runScene(Scene *scene);
    Window *getWindow();

    Game();
    ~Game();

    friend class Scene;
};


#endif //GAME_GAME_HPP
