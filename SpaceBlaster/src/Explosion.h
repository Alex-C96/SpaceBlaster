#pragma once
#include "GameObject.h"
#include "SDL.h"
#include <vector>


class Explosion : public GameObject {
public:
	Explosion(SDL_Renderer* renderer, float x, float y, std::vector<const char*>& imagePaths);
	virtual ~Explosion();

	virtual void update();
	virtual void render();

	bool isFinished() const;
private:
	int currentFrame;
	int frameCount;
	int frameWidth;
	int frameHeight;
	int animationSpeed;
	std::vector<SDL_Texture*> textures;
};

