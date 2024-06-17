//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "matrix/Camera.hpp"
#include "objects/Cube.hpp"
#include "shaders/ShaderProgram.hpp"
#include "shaders/ShaderFactory.hpp"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>

class TestScene : public Scene {
    private:
        void handleInput() {
            if (glfwGetKey(this->window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
                glfwSetInputMode(this->window->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);

            const float cameraSpeed = 2.5f * this->deltaTime;

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

        Camera camera = Camera();
        float deltaTime = 0.0f;
        Cube *cube;

        ShaderProgram *shaderProgram;

    protected:
        void init() override {

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

            this->shaderProgram = shaderFactory.finalize();

            this->cube = new Cube(*this->shaderProgram);
            //this->window->hideCursor();
        }

        void loop(float deltaTime) override {
            this->deltaTime = deltaTime;
            this->handleInput();

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            this->shaderProgram->use();

            this->shaderProgram->modifyUniform("projection", this->camera.createProjectionMatrix(this->window));
            this->shaderProgram->modifyUniform("view", camera.createViewMatrix());

            this->cube->draw();

            this->window->swapBuffers();
            glfwPollEvents();
        }

        void end() override {
            this->window->close();
        }

};

#endif //GAME_TESTSCENE_HPP
