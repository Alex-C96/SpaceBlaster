#pragma once
#include "SDL.h"

class GameObject {
public:
	GameObject(SDL_Renderer* renderer);
	virtual ~GameObject();

	void setPosition(float x, float y);
	void setSize(int width, int height);

	int getHealth() const;
	float getX() const;
	float getY() const;
	void setHealth(int health);
	void takeDamage(int damage);

protected:
	SDL_Renderer* renderer;
	SDL_Texture* createTexture(const char* imagePath);
	int health;
	float x;
	float y;
	int width;
	int height;
};