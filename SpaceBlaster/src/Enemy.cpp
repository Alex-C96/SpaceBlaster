#include "Enemy.h"
#include "Bullet.h"
#include <iostream>
#include <SDL_image.h>

Enemy::Enemy(SDL_Renderer* renderer, int x, int y) : GameObject(renderer) {

	texture = createTexture(renderer, "C:/Users/alexa/source/repos/SpaceBlaster/SpaceBlaster/assets/alien.png");
	setSize(32, 32);
	setPosition(x, y);
	setHealth(10);
	//setWaypoints();
	currentWaypoint = 0;

	srcRect = { 0, 0, width, height };
	destRect = { 0, 0, width, height };

	initialY = static_cast<float>(y);
	this->x = static_cast<float>(x);
	this->y = static_cast<float>(y);
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
	int bulletX = x;
	int bulletY = y;
	float bulletVelX = 0.0f;
	float bulletVelY = 5.0f;  // Adjust the bullet speed as needed
	bullets.push_back(new Bullet(renderer, bulletX, bulletY, bulletVelX, bulletVelY));
}

const std::vector<Bullet*>& Enemy::getBullets() const {
	return bullets;
}