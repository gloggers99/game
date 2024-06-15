//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "matrix/Camera.hpp"
#include "objects/Cube.hpp"
#include "vo/EBO.hpp"
#include "vo/VAO.hpp"
#include "vo/VBO.hpp"
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

        ShaderProgram shaderProgram = ShaderProgram();
        Camera camera = Camera();

        Cube *cube;
        Cube *cube2;

        float deltaTime = 0.0f;

    protected:
        void init() override {
            std::string vertexSource = R"glsl(
        #version 330 core
        layout (location = 0) in vec4 aPos;

        uniform mat4 transform = mat4(1.0f);
        uniform mat4 view;
        uniform mat4 projection;

        void main()
        {
            gl_Position = projection * view * transform * vec4(aPos.x, aPos.y, aPos.z, 1.0f);
            //gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
        }
        )glsl";

            Shader vertexShader = Shader(GL_VERTEX_SHADER, vertexSource);
            vertexShader.compileShader();

            std::string fragmentSource = R"glsl(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
        )glsl";

            Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, fragmentSource);
            fragmentShader.compileShader();

            this->shaderProgram.attachShader(vertexShader);
            this->shaderProgram.attachShader(fragmentShader);
            this->shaderProgram.link();

            this->cube = new Cube(this->shaderProgram);
            this->cube->translate(glm::vec3(0.0f, 1.0f, 0.0f));
            this->cube->scale(glm::vec3(0.5f, 0.5f, 0.5f));
            this->cube2 = new Cube(this->shaderProgram);
            this->cube2->translate(glm::vec3(0.0f, -1.0f, 0.0f));

            this->window->hideCursor();
        }

        void loop(float deltaTime) override {
            this->deltaTime = deltaTime;
            this->handleInput();
            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            shaderProgram.use();

            shaderProgram.modifyUniform("projection", this->camera.createProjectionMatrix(this->window));
            shaderProgram.modifyUniform("view", camera.createViewMatrix());


            this->cube->translate(glm::vec3(0.0f, -0.05f, 0.0f));
            this->cube->draw();
            this->cube2->draw();

            this->window->swapBuffers();
            glfwPollEvents();
        }

};

#endif //GAME_TESTSCENE_HPP
