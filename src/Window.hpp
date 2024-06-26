//
// Created by lucas on 6/10/24.
//

#ifndef GAME_WINDOW_HPP
#define GAME_WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>

class Window {
private:
    GLFWwindow *window;
public:
    void makeCurrentContext();
    void swapBuffers();
    GLFWwindow *getWindow();
    bool shouldClose();
    void close();
    void hideCursor();
    void showCursor();

    Window(int width, int height, const std::string& title);
    ~Window();
};


#endif //GAME_WINDOW_HPP
