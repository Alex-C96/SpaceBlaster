#pragma once

#include <SDL.h>
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player* player;
};