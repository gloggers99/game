#include "Game.hpp"
#include "TestScene.hpp"

// TODO: make texture filtering configurable

int main() {
    Game game = Game();
    TestScene ts1 = TestScene();
    game.runScene(&ts1);

    return 0;
}
