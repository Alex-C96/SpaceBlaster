#include "Enemy.h"
#include <iostream>
#include <SDL_image.h>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y) {

	texture = createTexture(renderer, "C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/alien.png");
	setSize(32, 32);
	setPosition(x, y);
	setHealth(10);

	srcRect = { 0, 0, width, height };
	destRect = { 0, 0, width, height };

	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

void Enemy::update() {
	// Enemy activity
	//x += 1;
}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_Rect newRect = destRect;
	newRect.x = static_cast<int>(x);
	newRect.y = static_cast<int>(y);
	SDL_RenderCopy(renderer, texture, &srcRect, &newRect);
}

SDL_Rect Enemy::getBoundingBox() const {
	SDL_Rect boundingBox = destRect;
	boundingBox.x = static_cast<int>(x);
	boundingBox.y = static_cast<int>(y);
	return boundingBox;
}
