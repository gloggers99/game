//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Window.hpp"
#include "shaders/ShaderProgram.hpp"

class Game;

// todo: add deltatime to loop parameters

class Scene {
private:
    bool run = true;
protected:
    Game *game{};
    Window *window{};
    ShaderProgram *defaultShaderProgram{};

    virtual void init() = 0;
    virtual void loop(float deltaTime) = 0;
    virtual void end() {
        this->run = false;
    }

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

    void setDefaultShaderProgram(ShaderProgram *shaderProgram) {
        this->defaultShaderProgram = shaderProgram;
    }
    ShaderProgram *getDefaultShaderProgram() {
        return this->defaultShaderProgram;
    }
public:
    Scene() = default;
    ~Scene() = default;

    friend class Game;
};


#endif //GAME_SCENE_HPP
