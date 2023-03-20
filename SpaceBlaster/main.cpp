#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (game.init("Spaceship Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN)) {
        game.run();
    }
    else {
        // Handle initialization error
    }

    return 0;
}