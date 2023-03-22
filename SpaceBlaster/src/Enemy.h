#pragma once
#include <SDL.h>

class Enemy {
public:
	Enemy(SDL_Renderer* renderer, int x, int y);
	virtual ~Enemy();

	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	SDL_Rect getBoundingBox() const;

protected:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;

	float x;
	float y;
};