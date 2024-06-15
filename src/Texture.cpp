#include "Texture.hpp"

#include <GL/gl.h>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <filesystem>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint Texture::getTexture() {
    return this->texture;
}

Texture::Texture(std::string texturePath) {
    if (!std::filesystem::exists(texturePath))
        throw std::runtime_error("texture file: \'" + texturePath + "\' doesn't exist");

    int width, height, channels;
    unsigned char *data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (!data)
        throw std::runtime_error("failed to load texture: " + texturePath);

    std::cout << "loading texture: " 
              << texturePath 
              << "\n"
              << "width: " 
              << width 
              << "\n" 
              << "height: " 
              << height 
              << "\n" 
              << "channels: " 
              << channels 
              << "\n";

    glGenTextures(1, &this->texture);
    glBindTexture(GL_TEXTURE_2D, this->texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
    glDeleteTextures(1, &this->texture);
}
