#include "Enemy.h"
#include <iostream>
#include <SDL_image.h>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y) {
	SDL_Surface* surface = IMG_Load("C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/alien.png");
	if (!surface) {
		// Handle error
		std::cout << "Surface error: " << SDL_GetError() << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	srcRect = { 0, 0, 32, 32 };
	destRect = { 0, 0, 32, 32 };

	this->x = static_cast<float>(x);
	this->x = static_cast<float>(y);
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

void Enemy::update() {
	// Enemy activity
	x += 1;
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
