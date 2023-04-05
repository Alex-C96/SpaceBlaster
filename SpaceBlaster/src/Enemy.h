#pragma once
#include <SDL.h>
#include "GameObject.h"
#include <vector>
#include "Bullet.h"

class Enemy : public GameObject {
public:
	Enemy(SDL_Renderer* renderer, float x, float y);
	virtual ~Enemy();

	virtual void update();
	virtual void render(SDL_Renderer* renderer);
	virtual void setWaypoints();
	virtual void setSineWaveMovement(float amplitude, float speed);
	SDL_Rect getBoundingBox() const;
	void shootBullet();
	const std::vector<Bullet*>& getBullets() const;

protected:
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect destRect;
	std::vector<SDL_Point> waypoints;
	std::vector<Bullet*> bullets;
	int currentWaypoint;
	float x;
	float y;
	float initialY;
	float amplitude;
	float speed;
	float wavelength = 200;
	int direction = 1;
	int screenWidth = 800;
	int shootCooldown = 0;
};