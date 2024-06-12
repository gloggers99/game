//
// Created by lucas on 6/10/24.
//

#ifndef GAME_VAO_HPP
#define GAME_VAO_HPP

#include "glad/gl.h"
#include <GLFW/glfw3.h>

class VAO {
private:
    GLuint vao;
public:
    GLuint getVAO();
    void bind();
    void unbind();

    VAO();
    ~VAO();
};


#endif //GAME_VAO_HPP
