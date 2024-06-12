//
// Created by lucas on 6/10/24.
//

#ifndef GAME_SHADER_HPP
#define GAME_SHADER_HPP

#include "glad/gl.h"
#include <GLFW/glfw3.h>
#include <string>

class Shader {
private:
    GLuint shader;
    const char *source;
public:
    GLuint getShader();
    void compileShader();

    Shader(GLint type, const std::string& shaderSource);
    ~Shader();
};


#endif //GAME_SHADER_HPP
