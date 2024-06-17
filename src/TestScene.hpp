//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "Texture.hpp"
#include "matrix/Camera.hpp"
#include "objects/Cube.hpp"

#include <cmath>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

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

        Texture texture = Texture("img/missing.jpeg");

    protected:
        void init() override {
            this->cube = new Cube(*this->defaultShaderProgram);

            this->window->hideCursor();
        }

        void loop(float deltaTime) override {
            this->deltaTime = deltaTime;
            this->handleInput();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            this->defaultShaderProgram->use();

            this->defaultShaderProgram->modifyUniform("projection", this->camera.createProjectionMatrix(this->window));
            this->defaultShaderProgram->modifyUniform("view", camera.createViewMatrix());

            this->cube->draw();

            this->window->swapBuffers();
        }

};

#endif //GAME_TESTSCENE_HPP
