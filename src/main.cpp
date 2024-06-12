#include <iostream>

#include "Game.hpp"
#include "TestScene.hpp"

int main() {
    Game game = Game();
    TestScene ts = TestScene();
    game.runScene(&ts);

    return 0;
}
