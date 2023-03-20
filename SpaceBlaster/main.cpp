#include <SDL.h>
#include <iostream>
#include "Game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init("Spaceship Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN)) {
        std::cerr << "Failed to initialize game: " << SDL_GetError() << std::endl;
        return 1;
    }

    while (game.isRunning()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.clean();

    return 0;
}