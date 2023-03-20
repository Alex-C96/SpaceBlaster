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
	destRect = { 400, 400, 32, 32 };
	x = 400;
	y = 400;
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

void Player::handleEvents(const Uint8* keyboardState, float deltaTime) {
    const float speed = 200.0f; // Adjust the speed value as needed

    velX = 0;
    velY = 0;

    if (keyboardState[SDL_SCANCODE_UP]) {
        velY -= speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        velY += speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        velX -= speed * deltaTime;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        velX += speed * deltaTime;
    }
}

void Player::update() {
    prevX = x;
    prevY = y;

    x += velX;
    y += velY;
}

float Player::lerp(float a, float b, float t) {
    return a + t * (b - a);
}

void Player::render(SDL_Renderer* renderer, float interpolation) {
    SDL_Rect interpolatedDestRect = destRect;
    interpolatedDestRect.x = static_cast<int>(lerp(prevX, x, interpolation));
    interpolatedDestRect.y = static_cast<int>(lerp(prevY, y, interpolation));
    SDL_RenderCopy(renderer, texture, &srcRect, &interpolatedDestRect);
}