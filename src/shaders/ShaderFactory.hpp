#ifndef GAME_SHADERFACTORY_HPP
#define GAME_SHADERFACTORY_HPP

#include "Shader.hpp"
#include "ShaderProgram.hpp"

#include <string>
#include <vector>
#include <typeinfo>

typedef struct {} sampler2D;

enum ShaderType {
    VERTEX,
    FRAGMENT
};

enum LayoutType {
    IN,
    OUT
};

class ShaderFactory {
private:
    std::string vertexShaderSource;
    std::string fragmentShaderSource;

    std::vector<std::string> uniforms;
    std::vector<std::string> layouts;

    void append(ShaderType shaderType, std::string input);

    template<typename T>
    std::string getGLType();

public:
    template<typename T>
    void uniform(std::string uniformName, ShaderType shaderType);

    template<typename T>
    void layout(int location, LayoutType layoutType, /* varType, */ std::string layoutName);

    template<typename T>
    void out(std::string varName, ShaderType shaderType);

    template<typename T>
    void in(std::string varName, ShaderType shaderType);

    void main(ShaderType shaderType, std::string content);

    ShaderProgram *finalize();

    ShaderFactory();
    ~ShaderFactory();
};



template<typename T>
std::string ShaderFactory::getGLType() {
    std::string output;

    if (typeid(T) == typeid(glm::vec4)) {
        output = "vec4";
    } else if (typeid(T) == typeid(glm::vec3)) {
        output = "vec3";
    } else if (typeid(T) == typeid(glm::vec2)) {
        output = "vec2";
    } else if (typeid(T) == typeid(glm::mat4)) {
        output = "mat4";
    } else if (typeid(T) == typeid(sampler2D)) {
        output = "sampler2D";
    }

    return output;
}

template<typename T>
void ShaderFactory::uniform(std::string uniformName, ShaderType shaderType) {
    std::string output = "uniform " + this->getGLType<T>() + " " + uniformName + ";\n";

    this->append(shaderType, output);

    this->uniforms.push_back(uniformName);
}

template<typename T>
void ShaderFactory::layout(int location, LayoutType layoutType, std::string layoutName) {
    std::string output =
            "layout (location = " + std::to_string(location) + ") "
            + (layoutType == LayoutType::IN ? "in" : "out") + " "
            + this->getGLType<T>() + " " + layoutName + ";\n";

    this->append(ShaderType::VERTEX, output);

    this->layouts.push_back(layoutName);
}

template<typename T>
void ShaderFactory::out(std::string varName, ShaderType shaderType) {
    std::string vertexOutput = "out " + this->getGLType<T>() + " " + varName + ";\n";

    this->append(shaderType, vertexOutput);
}

template<typename T>
void ShaderFactory::in(std::string varName, ShaderType shaderType) {
    std::string fragmentOutput = "in " + this->getGLType<T>() + " " + varName + ";\n";

    this->append(shaderType, fragmentOutput);
}

#endif //GAME_SHADERFACTORY_HPP
