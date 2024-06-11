//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SHADERPROGRAM_HPP
#define GAME_SHADERPROGRAM_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

class ShaderProgram {
private:
    GLuint shaderProgram;
    bool linked;

public:
    GLuint getShaderProgram();
    void attachShader(Shader shader);
    void link();
    void use();
    void modifyUniform(const std::string &uniformName, float r, float g, float b, float a);

    ShaderProgram();
    ~ShaderProgram();
};


#endif //GAME_SHADERPROGRAM_HPP
