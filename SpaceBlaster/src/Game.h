#pragma once
#include <vector>
#include "Enemy.h"
#include "FastEnemy.h"
#include <SDL.h>
#include "Player.h"
#include "Bullet.h"
#include "Explosion.h"

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
    bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);

private:
    bool running;
    SDL_Window* window;
    SDL_Renderer* renderer;
    Player* player;
    const int FIXED_TIMESTEP = 1000 / 60; // 60 updates per second (approx. 16.67 ms per update)
    std::vector<Enemy*> enemies;
    std::vector<const char*> explosionImagePaths;
    std::vector<Explosion*> explosions;
    SDL_Texture* backgroundTexture;
};