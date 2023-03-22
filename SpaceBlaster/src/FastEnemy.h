#pragma once
#include "Enemy.h"

class FastEnemy : public Enemy {
public:
	FastEnemy(SDL_Renderer* renderer, int x, int y);
	virtual ~FastEnemy();

	virtual void update() override;
};