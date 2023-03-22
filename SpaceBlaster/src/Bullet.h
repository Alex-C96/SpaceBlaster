#pragma once
#include <SDL.h>

class Bullet {
public:
    Bullet(SDL_Renderer* renderer, int x, int y, float velX, float velY);
    ~Bullet();

    void update();
    void render(SDL_Renderer* renderer);
    SDL_Rect getBoundingBox() const;
    bool isOffScreen() const;

private:
    SDL_Texture* texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;

    float x;
    float y;
    float velX;
    float velY;
};