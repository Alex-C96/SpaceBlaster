#include "FastEnemy.h"
#include <SDL_image.h>
#include <iostream>

FastEnemy::FastEnemy(SDL_Renderer* renderer, int x, int y) : Enemy(renderer, x, y) {
	SDL_Surface* surface = IMG_Load("C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/player.png");
	if (!surface) {
		// Handle error
		std::cout << "Surface error: " << SDL_GetError() << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

FastEnemy::~FastEnemy() {
}

void FastEnemy::update() {
	// Implement fast enemy-specific behavior
}