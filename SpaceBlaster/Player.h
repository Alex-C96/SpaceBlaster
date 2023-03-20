#pragma once

#include <SDL.h>

class Player {
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void handleEvents(SDL_Event& event);
	void update();
	void render(SDL_Renderer* renderer);

private:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	float x, y;
};