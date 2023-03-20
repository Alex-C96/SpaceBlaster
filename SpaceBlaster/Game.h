#pragma once

#include <SDL.h>
#include "Player.h"

class Game {
public:
    Game();
    ~Game();

    bool init(const char* title, int xpos, int ypos, int width, int height, int flags);
    void run();
    void handleEvents();
    void update();
    void render(float interpolation);
    void clean();
    bool isRunning();

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player* player;
    const int FIXED_TIMESTEP = 1000 / 60; // 60 updates per second (approx. 16.67 ms per update)
};