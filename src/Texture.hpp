#ifndef GAME_TEXTURE_HPP
#define GAME_TEXTURE_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>

class Texture {
private:
    GLuint texture;
    unsigned char *data;

public:
    GLuint getTexture();
    void bind();

    Texture(std::string texturePath);
    ~Texture();
};

#endif //GAME_TEXTURE_HPP
