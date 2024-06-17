//
// Created by lucas on 6/10/24.
//

#ifndef GAME_VBO_HPP
#define GAME_VBO_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class VBO {
private:
    GLuint vbo;
public:
    GLuint getVBO();
    void bind();
    void unbind();
    void setBufferData(float *data, size_t size);
    void setAttribPointer(GLint index, GLint size, int stride, int offset);

    VBO();
    ~VBO();
};


#endif //GAME_VBO_HPP
