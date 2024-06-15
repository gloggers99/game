//
// Created by lucas on 6/10/24.
//

#include <stdexcept>
#include "Window.hpp"

void Window::makeCurrentContext() {
    glfwMakeContextCurrent(this->window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(this->window);
}

GLFWwindow *Window::getWindow() {
    return this->window;
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(this->window);
}

void Window::close() {
    glfwSetWindowShouldClose(this->window, true);
}

void Window::hideCursor() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::showCursor() {
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

Window::Window(int width, int height, const std::string& title) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    this->window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window)
        throw std::runtime_error("failed to create window");
}

Window::~Window() {
    glfwDestroyWindow(this->window);
}

