//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "matrix/Camera.hpp"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO:
//  - control more of the scene class using Game.cpp

class TestScene : public Scene {
private:
    void handleInput() {
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

        const float cameraSpeed = 2.5f * this->deltaTime; // adjust accordingly

        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            this->camera.move(Direction::FORWARD, cameraSpeed);
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            this->camera.move(Direction::BACKWARD, cameraSpeed);
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            this->camera.move(Direction::LEFT, cameraSpeed);
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            this->camera.move(Direction::RIGHT, cameraSpeed);

        this->camera.handleMouse(this->window);
    }

    bool firstMouse = true;
    float yaw   = -90.0f;
    float pitch =  0.0f;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float fov   =  90.0f;

    ShaderProgram shaderProgram = ShaderProgram();
    Camera camera = Camera();

    VAO vao = VAO();
    VBO vbo = VBO();
    EBO ebo = EBO();

    float deltaTime = 0.0f;

protected:
    void init() override {
        std::string vertexSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec4 aPos;

        uniform mat4 transform;
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
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

        this->shaderProgram.attachShader(vertexShader);
        this->shaderProgram.attachShader(fragmentShader);
        this->shaderProgram.link();

        float vertices[] = {
                // front
                0.5f,  0.5f, -0.5f,  // top right
                0.5f, -0.5f, -0.5f,  // bottom right
                -0.5f, -0.5f, -0.5f,  // bottom left
                -0.5f,  0.5f, -0.5f,   // top left

                // right
                0.5f, 0.5f, 0.5f, // top right
                0.5f, -0.5f, 0.5f, // bottom right
                0.5f, -0.5f, -0.5f, // bottom left
                0.5f, 0.5f, -0.5f, // top left

                // left
                -0.5f, 0.5f, 0.5f, // top right
                -0.5f, -0.5f, 0.5f, // bottom right
                -0.5f, -0.5f, -0.5f, // bottom left
                -0.5f, 0.5f, -0.5f, // top left

                // back
                0.5f,  0.5f, 0.5f,  // top right
                0.5f, -0.5f, 0.5f,  // bottom right
                -0.5f, -0.5f, 0.5f,  // bottom left
                -0.5f,  0.5f, 0.5f,   // top left

                // top
                0.5f, 0.5f, 0.5f, // top right
                0.5f, 0.5f, -0.5f, // bottom right
                -0.5f, 0.5f, -0.5f, // bottom left
                -0.5f, 0.5f, 0.5f, // top left

                // bottom
                0.5f, -0.5f, 0.5f, // top right
                0.5f, -0.5f, -0.5f, // bottom right
                -0.5f, -0.5f, -0.5f, // bottom left
                -0.5f, -0.5f, 0.5f // top left

        };
        unsigned int indices[] = {  // note that we start from 0!
                // front
                0, 1, 3,   // first triangle
                1, 2, 3,    // second triangle

                // right
                4, 5, 7,
                5, 6, 7,

                // left
                8, 9, 11,
                9, 10, 11,

                // back
                12, 13, 15,
                13, 14, 15,

                // top
                16, 17, 19,
                17, 18, 19,

                // bottom
                20, 21, 23,
                21, 22, 23

        };


        vao.bind();

        vbo.bind();
        vbo.setBufferData(vertices, sizeof(vertices));

        ebo.bind();
        ebo.setBufferData(indices, sizeof(indices));
        vbo.setAttribPointer(0, 3);

        vao.unbind();

        shaderProgram.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 100.0f);
        shaderProgram.modifyUniform("projection", projection);

        glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    }

    void loop(float deltaTime) override {
        this->deltaTime = deltaTime;
        this->handleInput();
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        shaderProgram.use();

        float time = glfwGetTime();
        float greenValue = std::sin(time) + 0.5f;
        shaderProgram.modifyUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);

        glm::mat4 trans = glm::mat4(1.0f);
        shaderProgram.modifyUniform("transform", trans);
        shaderProgram.modifyUniform("view", camera.getMatrix());

        glBindVertexArray(vao.getVAO());
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        this->getGame()->getWindow()->swapBuffers();
        glfwPollEvents();
    }

};

#endif //GAME_TESTSCENE_HPP
