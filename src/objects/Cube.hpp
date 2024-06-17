#ifndef GAME_CUBE_HPP
#define GAME_CUBE_HPP

// TODO:
// - I think the correct way to go about generating shaders would be to
//   use preproccessor directives to indicate which shader features and
//   uniforms are needed. This way, the shader can be generated at runtime.

#include <glm/fwd.hpp>
#include <map>

#include "../shaders/ShaderProgram.hpp"

#include "../Texture.hpp"

#include "../vo/VAO.hpp"
#include "../vo/VBO.hpp"
#include "../vo/EBO.hpp"

enum Face {
    FRONTFACE,
    BACKFACE,
    LEFTFACE,
    RIGHTFACE,
    TOPFACE,
    BOTTOMFACE
};

class Cube {
private:
    glm::mat4 transform = glm::mat4(1.0f);
    // in the future we need a global shader program generator
    ShaderProgram &shaderProgram;

    Texture *topTexture;
    Texture *bottomTexture;
    Texture *frontTexture;
    Texture *backTexture;
    Texture *leftTexture;
    Texture *rightTexture;

    // i feel like we can abstract gpu objects more
    VAO vao;
    VBO vbo;
    EBO ebo;

public:
    void draw();

    void translate(glm::vec3 translation);
    void scale(glm::vec3 scale);

    void setTexture(Texture *texture); // set all sides to the same texture
    void setTexture(Texture *texture, Face face); // set a specific side to a texture
    void setTexture(std::map<Texture*, Face> textures); // set multiple sides to different textures

    Cube(ShaderProgram &shaderProgram);
    ~Cube();
};

#endif //GAME_CUBE_HPP
