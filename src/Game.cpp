//
// Created by lucas on 6/10/24.
//

#include <cmath>
#include <stdexcept>
#include <iostream>
#include <cmath>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Scene.hpp"
#include "Game.hpp"
#include "shaders/Shader.hpp"
#include "shaders/ShaderProgram.hpp"
#include "vo/VAO.hpp"
#include "vo/VBO.hpp"
#include "vo/EBO.hpp"

void Game::error_callback(int error, const char *description) {
    std::cerr << "GLFW Error: " << description << "\n";
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void Game::runScene(Scene *scene) {
    scene->setGame(this);
    scene->setWindow(this->window);
    scene->run();
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

}

Game::~Game() {
    glfwTerminate();
}

