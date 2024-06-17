//
// Created by lucas on 6/10/24.
//

#include <glm/fwd.hpp>
#include <stdexcept>
#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "shaders/ShaderFactory.hpp"
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
    scene->setDefaultShaderProgram(this->defaultShaderProgram);
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

Game::Game() : window(nullptr), defaultShaderProgram(nullptr) {
    if (!glfwInit())
        throw std::runtime_error("failed to initialize glfw");

    glfwSetErrorCallback(Game::error_callback);

    this->window = new Window(640, 480, "game");
    this->window->makeCurrentContext();

    gladLoadGL(glfwGetProcAddress);

    glViewport(0, 0, 640, 480);
    glfwSetFramebufferSizeCallback(this->window->getWindow(), Game::framebuffer_size_callback);
    glEnable(GL_DEPTH_TEST);

    ShaderFactory shaderFactory;
    shaderFactory.layout<glm::vec4>(0, LayoutType::IN, "aPos");
    shaderFactory.layout<glm::vec2>(1, LayoutType::IN, "aTexCoord");
    shaderFactory.out<glm::vec2>("texCoord", ShaderType::VERTEX);
    shaderFactory.uniform<glm::mat4>("transform", ShaderType::VERTEX);
    shaderFactory.uniform<glm::mat4>("view", ShaderType::VERTEX);
    shaderFactory.uniform<glm::mat4>("projection", ShaderType::VERTEX);
    shaderFactory.main(ShaderType::VERTEX, R"(
        gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        texCoord = aTexCoord;
    )");

    shaderFactory.out<glm::vec4>("fragColor", ShaderType::FRAGMENT);
    shaderFactory.in<glm::vec2>("texCoord", ShaderType::FRAGMENT);
    shaderFactory.uniform<sampler2D>("ourTexture", ShaderType::FRAGMENT);
    shaderFactory.main(ShaderType::FRAGMENT, R"(
        fragColor = texture(ourTexture, texCoord);
    )");

    this->defaultShaderProgram = shaderFactory.finalize();

    // default shader program
    /*
    std::string vertexSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec4 aPos;
        layout (location = 1) in vec2 aTexCoord;

        out vec2 TexCoord;

        uniform mat4 transform = mat4(1.0f);
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
            TexCoord = aTexCoord;
            //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        }
    )glsl";

    Shader vertexShader = Shader(GL_VERTEX_SHADER, vertexSource);
    vertexShader.compileShader();

    std::string fragmentSource = R"glsl(
        #version 330 core
        out vec4 FragColor;

        in vec2 TexCoord;

        uniform sampler2D ourTexture;

        void main()
        {
            //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            FragColor = texture(ourTexture, TexCoord);
        }
    )glsl";
    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fragmentSource);
    fragmentShader.compileShader();

    this->defaultShaderProgram->attachShader(vertexShader);
    this->defaultShaderProgram->attachShader(fragmentShader);
    this->defaultShaderProgram->link();
    */
}

Game::~Game() {
    glfwTerminate();
}

