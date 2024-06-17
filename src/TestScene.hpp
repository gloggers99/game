//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "matrix/Camera.hpp"
#include "objects/Cube.hpp"

#include <cmath>

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

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

            //this->camera.handleMouse(this->window);
        }

        Camera camera = Camera();

        float deltaTime = 0.0f;

        Cube *cube;

    protected:
        void init() override {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO &io = ImGui::GetIO();
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            ImGui_ImplGlfw_InitForOpenGL(this->window->getWindow(), true);
            ImGui_ImplOpenGL3_Init();


            this->cube = new Cube(*this->defaultShaderProgram);

            //this->window->hideCursor();
        }

        void loop(float deltaTime) override {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            {
                ImGui::Begin("Hello, world!");
                ImGui::Text("This is some useful text.");
                ImGui::End();
            }

            this->deltaTime = deltaTime;
            this->handleInput();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            this->defaultShaderProgram->use();

            this->defaultShaderProgram->modifyUniform("projection", this->camera.createProjectionMatrix(this->window));
            this->defaultShaderProgram->modifyUniform("view", camera.createViewMatrix());

            this->cube->draw();

            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

            this->window->swapBuffers();
        }

        void end() override {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();
            ImGui::DestroyContext();
            this->window->close();
        }

};

#endif //GAME_TESTSCENE_HPP
