#include "Player.h"
#include <iostream>
#include <SDL_image.h>

Player::Player(SDL_Renderer* renderer) : GameObject(renderer) {
    shootCooldown = 0;

	// Load the player sprite
    texture = createTexture("../SpaceBlaster/assets/player/greyblue_01.png");
    setPosition(400, 400);
    setSize(48, 48);
    setHealth(100);
    prevX = 0;
    prevY = 0;

	srcRect = { 0, 0, width, height };
	destRect = { static_cast<int>(x), static_cast<int>(y), width, height };
}

Player::~Player() {
	SDL_DestroyTexture(texture);
}

void Player::handleEvents(const Uint8* keyboardState, float deltaTime) {
    const float speed = 200.0f; // Adjust the speed value as needed
    velX = 0;
    velY = 0;

    if (shootCooldown > 0) {
        shootCooldown -= deltaTime;
    }

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
    if (keyboardState[SDL_SCANCODE_SPACE] && shootCooldown <= 0) {
        shootBullet(renderer);
        shootCooldown = shootDelay;
    }
}

void Player::update() {
    prevX = x;
    prevY = y;
    
    x += velX;
    y += velY;

    for (size_t i = 0; i < bullets.size(); ) {
        bullets[i]->update();

        // Check if the bullet is off the screen  --TODO check if bullet has hit enemy
        if (bullets[i]->isOffScreen() || bullets[i]->hitEnemy == true) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
        else {
            ++i;
        }
    }
    setPosition(x, y);
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

SDL_Rect Player::getBoundingBox() const {
    SDL_Rect boundingBox = destRect;
    boundingBox.x = static_cast<int>(x);
    boundingBox.y = static_cast<int>(y);
    return boundingBox;
}

void Player::shootBullet(SDL_Renderer* renderer) {
    int bulletX = static_cast<int>(x) + (destRect.w / 2) - 10;
    int bulletY = static_cast<int>(y) - 10;
    float bulletVelX = 0.0f;
    float bulletVelY = -5.0f;  // Adjust the bullet speed as needed
    bullets.push_back(new Bullet(renderer, bulletX, bulletY, bulletVelX, bulletVelY));
}

const std::vector<Bullet*>& Player::getBullets() const {
    return bullets;
}