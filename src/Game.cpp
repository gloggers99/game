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

#include "Game.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

void Game::error_callback(int error, const char *description) {
    std::cerr << "GLFW Error: " << description << "\n";
}

void Game::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
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

    std::string vertexSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec4 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )glsl";

    Shader vertexShader = Shader(GL_VERTEX_SHADER, vertexSource);
    vertexShader.compileShader();

    std::string fragmentSource = R"glsl(
        #version 330 core
        out vec4 FragColor;

        uniform vec4 ourColor;

        void main()
        {
            //FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            FragColor = ourColor;
        }
    )glsl";

    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fragmentSource);
    fragmentShader.compileShader();

    ShaderProgram shaderProgram = ShaderProgram();
    shaderProgram.attachShader(vertexShader);
    shaderProgram.attachShader(fragmentShader);
    shaderProgram.link();

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    VAO vao = VAO();
    VBO vbo = VBO();
    EBO ebo = EBO();

    vao.bind();

    vbo.bind();
    vbo.setBufferData(vertices, sizeof(vertices));

    ebo.bind();
    ebo.setBufferData(indices, sizeof(indices));
    vbo.setAttribPointer(0, 3);

    vao.unbind();

    while (!this->window->shouldClose()) {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.use();

        float time = glfwGetTime();
        float greenValue = std::sin(time) + 0.5f;
        shaderProgram.modifyUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(vao.getVAO());
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        this->window->swapBuffers();
        glfwPollEvents();
    }
}

Game::~Game() {
    glfwTerminate();
}

