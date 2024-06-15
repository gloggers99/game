#ifndef GAME_CUBE_HPP
#define GAME_CUBE_HPP

// TODO:
// - I think the correct way to go about generating shaders would be to
//   use preproccessor directives to indicate which shader features and
//   uniforms are needed. This way, the shader can be generated at runtime.

#include <glm/fwd.hpp>

#include "../shaders/ShaderProgram.hpp"

#include "../vo/VAO.hpp"
#include "../vo/VBO.hpp"
#include "../vo/EBO.hpp"

class Cube {
private:
    glm::mat4 transform = glm::mat4(1.0f);
    // in the future we need a global shader program generator
    ShaderProgram &shaderProgram;

    // i feel like we can abstract gpu objects more
    VAO vao;
    VBO vbo;
    EBO ebo;

public:
    void draw();

    void translate(glm::vec3 translation);

    Cube(ShaderProgram &shaderProgram);
    ~Cube();
};

#endif //GAME_CUBE_HPP
