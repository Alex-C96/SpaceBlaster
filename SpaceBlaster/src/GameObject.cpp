#include "GameObject.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

GameObject::GameObject() {}

GameObject::~GameObject() {}

SDL_Texture* GameObject::createTexture(SDL_Renderer* renderer, const char* imagePath) {
	SDL_Surface* surface = IMG_Load(imagePath);
	if (!surface) {
		std::cout << "Surface error: " << SDL_GetError() << std::endl;
		return nullptr;
	}

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	return newTexture;
}

void GameObject::setPosition(float x, float y) {
	this->x = x;
	this->y = y;
}

void GameObject::setSize(int width, int height) {
	this->width = width;
	this->height = height;
}

int GameObject::getHealth() const {
	return health;
}

void GameObject::setHealth(int health) {
	this->health = health;
}

void GameObject::takeDamage(int damage) {
	health -= damage;
}
