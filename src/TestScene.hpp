//
// Created by lucas on 6/11/24.
//

#ifndef GAME_TESTSCENE_HPP
#define GAME_TESTSCENE_HPP

#include "Scene.hpp"
#include <cmath>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// TODO:
//  - setup deltatime, control more of the scene class using Game.cpp

class TestScene : public Scene {
private:
    void handleInput() {
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
            this->getGame()->getWindow()->close();
        const float cameraSpeed = 0.05f; // adjust accordingly
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(this->window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
public:
    void run() override {
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

        ShaderProgram shaderProgram = ShaderProgram();
        shaderProgram.attachShader(vertexShader);
        shaderProgram.attachShader(fragmentShader);
        shaderProgram.link();

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

        shaderProgram.use();
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float) 640 / (float) 480, 0.1f, 100.0f);
        shaderProgram.modifyUniform("projection", projection);

        while (!this->getGame()->getWindow()->shouldClose()) {
            this->handleInput();

            glClear(GL_COLOR_BUFFER_BIT);
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            shaderProgram.use();

            float time = glfwGetTime();
            float greenValue = std::sin(time) + 0.5f;

            shaderProgram.modifyUniform("ourColor", 0.0f, greenValue, 0.0f, 1.0f);


            glm::mat4 trans = glm::mat4(1.0f);
            //trans = glm::rotate(trans, glm::radians(50.0f), glm::vec3(1.0, 1.0, 1.0));
            //trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));

            shaderProgram.modifyUniform("transform", trans);

            /*
            glm::mat4 view = glm::mat4(1.0f);
            float radius = 10.0f;
            float camX = static_cast<float>(sin(glfwGetTime()) * radius);
            float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
            view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
                               glm::vec3(0.0f, 0.0f, 0.0f),
                               glm::vec3(0.0f, 1.0f, 0.0f));
            */
            glm::mat4 view = glm::mat4(1.0f);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
            shaderProgram.modifyUniform("view", view);

            glBindVertexArray(vao.getVAO());
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

            this->getGame()->getWindow()->swapBuffers();
            glfwPollEvents();
        }
    }
};

#endif //GAME_TESTSCENE_HPP
