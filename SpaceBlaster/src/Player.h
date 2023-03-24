#pragma once

#include <SDL.h>
#include <vector>
#include "Bullet.h"

class Player {
public:
	Player(SDL_Renderer* renderer);
	~Player();

	void handleEvents(const Uint8* keyboardState, float deltaTime);
	void update();
	void render(SDL_Renderer* renderer, float interpolation);
	SDL_Rect getBoundingBox() const;
	const std::vector<Bullet*>& getBullets() const;
	void shootBullet(SDL_Renderer* renderer);

private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	float x;
	float y;
	float prevX;
	float prevY;
	float velX;
	float velY;
	std::vector<Bullet*> bullets;
	float shootCooldown;
	const float shootDelay = 15.0f;

	float lerp(float a, float b, float t);
};