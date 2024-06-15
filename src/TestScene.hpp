//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include "Texture.hpp"
#include "matrix/Camera.hpp"
#include "shaders/Shader.hpp"
#include <GL/gl.h>
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

        float deltaTime = 0.0f;

        VAO vao;
        VBO vbo;

        Texture texture = Texture("img/wall.jpg");

    protected:
        void init() override {
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

            this->shaderProgram.attachShader(vertexShader);
            this->shaderProgram.attachShader(fragmentShader);
            this->shaderProgram.link();

            float vertices[] = {
                 0.5f, -0.5f, 0.0f,     0.5f, -0.5f, // bottom right
                -0.5f, -0.5f, 0.0f,    -0.5f, -0.5f, // bottom left
                 0.0f,  0.5f, 0.0f,     0.0f,  0.5f  // top
            };

            this->vao.bind();
            this->vbo.bind();
            this->vbo.setBufferData(vertices, sizeof(vertices));
            this->vbo.setAttribPointer(0, 3, 5 * sizeof(float), 0);
            this->vbo.setAttribPointer(1, 2, 5 * sizeof(float), 3);
            this->vbo.unbind();
            this->vao.unbind();

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

            glBindTexture(GL_TEXTURE_2D, this->texture.getTexture());
            this->vao.bind();
            glDrawArrays(GL_TRIANGLES, 0, 3);
            this->vao.unbind();

            this->window->swapBuffers();
            glfwPollEvents();
        }

};

#endif //GAME_TESTSCENE_HPP
