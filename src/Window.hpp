//
// Created by lucas on 6/10/24.
//

#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <GLFW/glfw3.h>

class Window {
private:
    GLFWwindow *window;
public:
    void makeCurrentContext();
    void swapBuffers();
    GLFWwindow *getWindow();
    bool shouldClose();
    void close();

    Window(int width, int height, const std::string& title);
    ~Window();
};


#endif //GAME_WINDOW_HPP
