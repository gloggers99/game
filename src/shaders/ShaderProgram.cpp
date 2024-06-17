//
// Created by lucas on 6/11/24.
//

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.hpp"
#include "ShaderFactory.hpp"

GLuint ShaderProgram::getShaderProgram() {
    return this->shaderProgram;
}

void ShaderProgram::attachShader(Shader shader) {
    glAttachShader(this->shaderProgram, shader.getShader());
    this->shaders.push_back(shader);
}

void ShaderProgram::link() {
    glLinkProgram(this->shaderProgram);
    for (Shader &shader : this->shaders) {
        int success;
        char infoLog[512];
        glGetShaderiv(shader.getShader(), GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader.getShader(), 512, NULL, infoLog);
            std::cout << "shader failed to compile!:\n\n" << infoLog << "\n";
        }
    }
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

void ShaderProgram::modifyUniform(const std::string &uniformName, glm::mat4 mat4) {
    this->use();
    GLint uniformLocation = glGetUniformLocation(this->shaderProgram, uniformName.c_str());
    if (uniformLocation == -1)
        std::cerr << "failed to find uniform \"" + uniformName + "\"\n";
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mat4));
}

ShaderProgram::ShaderProgram() : linked(false) {
    this->shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->shaderProgram);
}

