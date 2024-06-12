#include <iostream>

#include "Game.hpp"
#include "TestScene.hpp"
#include "TestScene2.hpp"

int main() {
    Game game = Game();
    TestScene ts1 = TestScene();
    TestScene2 ts2 = TestScene2();
    game.runScene(&ts2);

    return 0;
}
