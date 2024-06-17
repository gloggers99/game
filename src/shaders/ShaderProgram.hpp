//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SHADERPROGRAM_HPP
#define GAME_SHADERPROGRAM_HPP

#include <vector>
#include <glm/glm.hpp>

#include "Shader.hpp"

class ShaderProgram {
private:
    GLuint shaderProgram;
    bool linked;
    std::vector<Shader> shaders;

public:
    GLuint getShaderProgram();
    void attachShader(Shader shader);
    void link();
    void use();
    void modifyUniform(const std::string &uniformName, float r, float g, float b, float a);
    void modifyUniform(const std::string &uniformName, glm::mat4 mat4);

    ShaderProgram();
    ~ShaderProgram();
};


#endif //GAME_SHADERPROGRAM_HPP
