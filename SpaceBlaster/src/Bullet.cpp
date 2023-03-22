#include "Bullet.h"
#include <SDL_image.h>
#include <iostream>

Bullet::Bullet(SDL_Renderer* renderer, int x, int y, float velX, float velY)
	: x(x), y(y), velX(velX), velY(velY) {
	SDL_Surface* surface = IMG_Load("C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/bullet.png");
	if (!surface) {
		// Handle error
		std::cout << "Surface error: " << SDL_GetError() << std::endl;
	}
	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srcRect = { 0, 0, 16, 24 };
	destRect = { x, y, 16, 24 };
}

Bullet::~Bullet() {
	SDL_DestroyTexture(texture);
}

void Bullet::update() {
	x += velX;
	y += velY;
	destRect.x = static_cast<int>(x);
	destRect.y = static_cast<int>(y);
}

void Bullet::render(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}

SDL_Rect Bullet::getBoundingBox() const {
	return destRect;
}

bool Bullet::isOffScreen() const {
	return y < 0;
}