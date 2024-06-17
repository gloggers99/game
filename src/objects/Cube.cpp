#include "Cube.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>

void Cube::draw() {
    this->vao.bind();
    this->shaderProgram.use();
    this->shaderProgram.modifyUniform("transform", this->transform);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    this->shaderProgram.modifyUniform("transform", glm::mat4(1.0f));
    this->vao.unbind();
}

void Cube::translate(glm::vec3 translation) {
    this->transform = glm::translate(this->transform, translation);
}

void Cube::scale(glm::vec3 scale) {
    this->transform = glm::scale(this->transform, scale);
}

Cube::Cube(ShaderProgram &shaderProgram) 
    : shaderProgram(shaderProgram),
    vao(VAO()),
    vbo(VBO()), 
    ebo(EBO()) {
        // deal with the gpu objects
        float cubeVertices[] = {
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
        unsigned int cubeIndices[] = {  // note that we start from 0!
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

        // TODO: in the future we need to make a 
        //       class to generate these vertices and indices.

        this->vao.bind();

        this->vbo.bind();
        this->vbo.setBufferData(cubeVertices, sizeof(cubeVertices));
        this->vbo.setAttribPointer(0, 3, 3 * sizeof(float), 0);

        this->ebo.bind();
        this->ebo.setBufferData(cubeIndices, sizeof(cubeIndices));

        this->vao.unbind();
    }

Cube::~Cube() {
}
