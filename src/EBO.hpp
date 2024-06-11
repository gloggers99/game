//
// Created by lucas on 6/11/24.
//

#ifndef GAME_EBO_HPP
#define GAME_EBO_HPP

#include <glad/gl.h>
#include <GLFW/glfw3.h>

class EBO {
private:
    GLuint ebo;
public:
    GLuint getEBO();
    void bind();
    void unbind();
    void setBufferData(unsigned int *indices, size_t size);

    EBO();
    ~EBO();
};


#endif //GAME_EBO_HPP
