#include "Player.h"
#include <iostream>
#include <SDL_image.h>

Player::Player(SDL_Renderer* renderer) {
	// Load the player sprite
	SDL_Surface* surface = IMG_Load("C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/player.png");
	if (!surface) {
		// Handle error
        std::cout << "Surface error: " << SDL_GetError() << std::endl;
    }

	texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	srcRect = { 0, 0, 32, 32 }; // Assuming the player sprite is 32x32 pixels
	destRect = { 100, 100, 32, 32 };
	x = 100;
	y = 100;
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

void Player::handleEvents(SDL_Event& event) {
    // Handle player input
    switch (event.type) {
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym) {
        case SDLK_UP:
            y -= 5;
            break;
        case SDLK_DOWN:
            y += 5;
            break;
        case SDLK_LEFT:
            x -= 5;
            break;
        case SDLK_RIGHT:
            x += 5;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Player::update() {
    destRect.x = static_cast<int>(x);
    destRect.y = static_cast<int>(y);
}

void Player::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
}