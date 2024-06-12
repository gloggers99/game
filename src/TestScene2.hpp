//
// Created by lucas on 6/12/24.
//

#ifndef GAME_TESTSCENE2_HPP
#define GAME_TESTSCENE2_HPP

#include "Scene.hpp"

class TestScene2 : public Scene {
protected:
    void init() override {

    }

    void loop() override {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        this->window->swapBuffers();
    }
};

#endif //GAME_TESTSCENE2_HPP
