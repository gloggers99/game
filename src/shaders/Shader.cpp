//
// Created by lucas on 6/10/24.
//

#include "Shader.hpp"

GLuint Shader::getShader() {
    return this->shader;
}

void Shader::compileShader() {
    glCompileShader(this->shader);
}

Shader::Shader(GLint type, const std::string& shaderSource) {
    this->shader = glCreateShader(type);
    this->source = shaderSource.c_str();
    glShaderSource(this->shader, 1, &this->source, nullptr);
}

Shader::~Shader() {

}
