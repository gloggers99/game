#include "ShaderFactory.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include <glm/fwd.hpp>

#include <stdexcept>
#include <string>
#include <iostream>

void ShaderFactory::append(ShaderType shaderType, std::string input) {
    switch (shaderType) {
        case ShaderType::VERTEX:
            this->vertexShaderSource += input;
            break;
        case ShaderType::FRAGMENT:
            this->fragmentShaderSource += input;
            break;
        default:
            throw std::runtime_error("invalid ShaderType provided");
    }
}

void ShaderFactory::main(ShaderType shaderType, std::string content) {
    this->append(shaderType, "void main() {\n" + content + "\n}\n");
}

ShaderProgram *ShaderFactory::finalize() {
    ShaderProgram *program = new ShaderProgram();

    std::cout << this->vertexShaderSource << "\n\n";
    std::cout << this->fragmentShaderSource << "\n\n";

    Shader vertexShader = Shader(GL_VERTEX_SHADER, this->vertexShaderSource);
    vertexShader.compileShader();
    
    Shader fragmentShader = Shader(GL_FRAGMENT_SHADER, this->fragmentShaderSource);
    fragmentShader.compileShader();

    program->attachShader(vertexShader);
    program->attachShader(fragmentShader);
    program->link();

    return program;
}

ShaderFactory::ShaderFactory() {
    this->vertexShaderSource += R"(
#version 330 core

    )";
    this->fragmentShaderSource += R"(
#version 330 core

    )";
}

ShaderFactory::~ShaderFactory() {

}
