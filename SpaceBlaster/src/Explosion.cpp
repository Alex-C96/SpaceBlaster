#include "Explosion.h"
#include "SDL_image.h"

Explosion::Explosion(SDL_Renderer* renderer, float x, float y, std::vector<const char*>& imagePaths)
	: GameObject(renderer), currentFrame(0), frameCount(11), frameWidth(64), frameHeight(64), animationSpeed(10) {
	this->x = x;
	this->y = y;

	for (const char* imagePath : imagePaths) {
		SDL_Texture* texture = createTexture(imagePath);
		textures.push_back(texture);
	}
}

Explosion::~Explosion() {
	for (SDL_Texture* texture : textures) {
		SDL_DestroyTexture(texture);
	}
}

void Explosion::update() {
	currentFrame += animationSpeed;
}

void Explosion::render() {
	if (currentFrame < frameCount * animationSpeed) {
		int frameIndex = currentFrame / animationSpeed;
		SDL_Rect destRect = { x, y, frameWidth, frameHeight };
		SDL_RenderCopy(renderer, textures[frameIndex], nullptr, &destRect);
	}
}

bool Explosion::isFinished() const {
	return currentFrame >= frameCount * animationSpeed;
}