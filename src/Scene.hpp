//
// Created by lucas on 6/11/24.
//

#ifndef GAME_SCENE_HPP
#define GAME_SCENE_HPP

#include "Game.hpp"

class Scene {
private:
public:
    virtual void run() = 0;

    Scene() = default;
    ~Scene() = default;

    friend class Game;
};


#endif //GAME_SCENE_HPP
