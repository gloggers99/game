//
// Created by lucas on 6/11/24.
//

#include <iostream>
#include "ShaderProgram.hpp"

GLuint ShaderProgram::getShaderProgram() {
    return this->shaderProgram;
}

void ShaderProgram::attachShader(Shader shader) {
    glAttachShader(this->shaderProgram, shader.getShader());
}

void ShaderProgram::link() {
    glLinkProgram(this->shaderProgram);
    this->linked = true;
}

void ShaderProgram::use() {
    glUseProgram(this->shaderProgram);
}

void ShaderProgram::modifyUniform(const std::string &uniformName, float r, float g, float b, float a) {
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    if (uniformLocation == -1)
        std::cerr << "failed to find uniform \"" + uniformName + "\"\n";
    glUniform4f(uniformLocation, r, g, b, a);
}

ShaderProgram::ShaderProgram() : linked(false) {
    this->shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->shaderProgram);
}

