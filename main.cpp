#include <stdlib.h>
#include "game.hpp"

int main()
{

    Game game;
    Game::init();
    game.run();

    return EXIT_SUCCESS;
}