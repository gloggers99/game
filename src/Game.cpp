//
// Created by lucas on 6/10/24.
//

#include <stdexcept>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Game.hpp"

void Game::error_callback(int error, const char *description) {
    std::cerr << "GLFW Error: " << description << "\n";
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::runScene(Scene *scene) {
    scene->setGame(this);
    scene->setWindow(this->window);
    scene->init();
    float lastFrame = 0.0f;
    while (scene->run) {
        if (window->shouldClose())
            break;
        float currentFrame = static_cast<float>(glfwGetTime());
        scene->loop(currentFrame - lastFrame);
        lastFrame = currentFrame;
        glfwPollEvents();
    }
}

Window *Game::getWindow() {
    return this->window;
}

Game::Game() : window(nullptr) {
    if (!glfwInit())
        throw std::runtime_error("failed to initialize glfw");

    glfwSetErrorCallback(Game::error_callback);

    this->window = new Window(640, 480, "game");
    this->window->makeCurrentContext();

    gladLoadGL(glfwGetProcAddress);

    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(this->window->getWindow(), Game::framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);
}

Game::~Game() {
    glfwTerminate();
}

