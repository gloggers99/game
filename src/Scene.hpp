//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Scene.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

class Game;

class Scene {
private:
    Game *game;
public:
    virtual void run() = 0;

    void setGame(Game *game) {
        this->game = game;
    }

    Game *getGame() {
        return this->game;
    }

    Scene() = default;
    ~Scene() = default;

    friend class Game;
};


#endif //GAME_SCENE_HPP
