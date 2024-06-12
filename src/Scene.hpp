//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
#include "shaders/Shader.hpp"
#include "shaders/ShaderProgram.hpp"
#include "vo/VAO.hpp"
#include "vo/VBO.hpp"
#include "vo/EBO.hpp"
#include "Window.hpp"

class Game;

class Scene {
protected:
    Game *game;
    Window *window;
public:
    virtual void run() = 0;

    void setGame(Game *game) {
        this->game = game;
    }

    Game *getGame() {
        return this->game;
    }

    void setWindow(Window *window) {
        this->window = window;
    }

    Window *getWindow() {
        return this->window;
    }

    Scene() = default;
    ~Scene() = default;

    friend class Game;
};


#endif //GAME_SCENE_HPP
