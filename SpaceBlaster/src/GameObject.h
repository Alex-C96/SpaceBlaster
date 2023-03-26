#pragma once
#include "SDL.h"

class GameObject {
public:
	GameObject();
	virtual ~GameObject();

	void setPosition(float x, float y);
	void setSize(int width, int height);

	int getHealth() const;
	void setHealth(int health);
	void takeDamage(int damage);

protected:
	SDL_Texture* createTexture(SDL_Renderer* renderer, const char* imagePath);
	int health;
	float x;
	float y;
	int width;
	int height;
};