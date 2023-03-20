#pragma once

#include <SDL.h>

class Player {
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void handleEvents(const Uint8* keyboardState, float deltaTime);
	void update();
	void render(SDL_Renderer* renderer, float interpolation);

private:
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	float x;
	float y;
	float prevX;
	float prevY;
	float velX;
	float velY;

	float lerp(float a, float b, float t);
};