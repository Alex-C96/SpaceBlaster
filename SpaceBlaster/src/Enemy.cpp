#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include <SDL_image.h>

Enemy::Enemy(SDL_Renderer* renderer, float x, float y) : GameObject(renderer) {
	texture = createTexture("../SpaceBlaster/assets/enemies/bug_1.png");
	setSize(64, 64);
	setPosition(x, y);
	setHealth(10);
	//setWaypoints();
	currentWaypoint = 0;

	srcRect = { 0, 0, width, height };
	destRect = { static_cast<int>(x), static_cast<int>(y), width, height };
	
	initialY = static_cast<float>(y);
}

Enemy::~Enemy() {
	SDL_DestroyTexture(texture);
}

void Enemy::update() {
	// get current waypoint
	//SDL_Point target = waypoints[currentWaypoint];

	//// calculate direction vector
	//float dirX = target.x - x;
	//float dirY = target.y - y;
	//float distance = std::sqrt(dirX * dirX + dirY * dirY);

	//// normalize direction vector
	//dirX /= distance;
	//dirY /= distance;

	//// move enemies along direction vector
	//float speed = 2.0f;
	//x += dirX * speed;
	//y += dirY * speed;

	//destRect.x = static_cast<int>(x);
	//destRect.y = static_cast<int>(y);

	//// Check if the enemy has reach the current waypoint
	//float threshold = 5.0f;
	//if (distance < threshold) {
	//	currentWaypoint = (currentWaypoint + 1) % waypoints.size();
	//}
	
	shootCooldown++;
	
	if (shootCooldown >= 50) {
		shootBullet();
		shootCooldown = 0;
	}

	x += speed * direction;
	y = initialY + amplitude * std::sin(x * 2 * M_PI / wavelength);

	if (x <= 0 || x >= screenWidth - destRect.w) {
		direction = -direction;
	}
	
	setPosition(x, y);
}

void Enemy::render(SDL_Renderer* renderer) {
	SDL_Rect newRect = destRect;
	newRect.x = static_cast<int>(x);
	newRect.y = static_cast<int>(y);
	SDL_RenderCopy(renderer, texture, &srcRect, &newRect);
}

SDL_Rect Enemy::getBoundingBox() const {
	SDL_Rect boundingBox = destRect;
	boundingBox.x = static_cast<int>(x);
	boundingBox.y = static_cast<int>(y);
	return boundingBox;
}

void Enemy::setWaypoints() {
	waypoints.push_back({ 100, 100 });
	waypoints.push_back({ 200, 100 });
	waypoints.push_back({ 200, 200 });
	waypoints.push_back({ 100, 200 });
}

void Enemy::setSineWaveMovement(float amplitude, float speed) {
	this->amplitude = amplitude;
	this->speed = speed;
}

void Enemy::shootBullet() {
	int bulletX = static_cast<int>(x) + (destRect.w / 2) - 5;
	int bulletY = static_cast<int>(y) + 30;
	float bulletVelX = 0.0f;
	float bulletVelY = 5.0f;  // Adjust the bullet speed as needed
	bullets.push_back(new Bullet(renderer, bulletX, bulletY, bulletVelX, bulletVelY));
}

const std::vector<Bullet*>& Enemy::getBullets() const {
	return bullets;
}