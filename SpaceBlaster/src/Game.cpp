#include "Game.h"
#include "Player.h"
#include "SDL_image.h"
#include <iostream>
#include <SFML/Graphics.hpp>

Game::Game() : running(false), window(nullptr), renderer(nullptr), player(nullptr) {
}

Game::~Game() {
}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Init Error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Initialize SDL_image for PNG support
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		return false;
	}

	window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
	if (!window) {
		std::cout << "Window error: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "Window Created" << std::endl;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Render error: " << SDL_GetError() << std::endl;
		return false;
	}

	// Create background Image
	SDL_Surface* backgroundSurface = IMG_Load("../SpaceBlaster/assets/stars_background.png");
	if (!backgroundSurface) {
		std::cout << "Background image error: " << IMG_GetError() << std::endl;
		return false;
	}

	backgroundTexture = SDL_CreateTextureFromSurface(renderer, backgroundSurface);
	SDL_FreeSurface(backgroundSurface);

	// Create Explosions vector
	std::vector<const char*> explosionImagePaths = {
		"../SpaceBlaster/assets/explosions/explosion-01.png",
		"../SpaceBlaster/assets/explosions/explosion-02.png",
		"../SpaceBlaster/assets/explosions/explosion-03.png",
		"../SpaceBlaster/assets/explosions/explosion-04.png",
		"../SpaceBlaster/assets/explosions/explosion-05.png",
		"../SpaceBlaster/assets/explosions/explosion-06.png",
		"../SpaceBlaster/assets/explosions/explosion-07.png",
		"../SpaceBlaster/assets/explosions/explosion-08.png",
		"../SpaceBlaster/assets/explosions/explosion-09.png",
		"../SpaceBlaster/assets/explosions/explosion-10.png",
		"../SpaceBlaster/assets/explosions/explosion-11.png"
	};
	this->explosionImagePaths = explosionImagePaths;

	// Create player and enemies
	player = new Player(renderer);
	int x = 80;
	int y = 50;
	for (int i = 0; i < 1; i++) {
		enemies.push_back(new Enemy(renderer, x, y));
		enemies[i]->setSineWaveMovement(50.0f, 1.0f);
		x += 150;
		y += 50;
	}
	//enemies.push_back(new FastEnemy(renderer, 200, 200));

	running = true;
	return true;
}

void Game::run() {
	Uint32 lastUpdate = SDL_GetTicks();
	Uint32 accumulator = 0;

	while (isRunning()) {
		Uint32 currentTicks = SDL_GetTicks();
		Uint32 frameTime = currentTicks - lastUpdate;
		lastUpdate = currentTicks;

		accumulator += frameTime;

		handleEvents();

		while (accumulator >= FIXED_TIMESTEP) {
			update();
			accumulator -= FIXED_TIMESTEP;
		}

		float interpolation = static_cast<float>(accumulator) / FIXED_TIMESTEP;
		render(interpolation);
	}

	clean();
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			running = false;
		}
	}

	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	float deltaTime = static_cast<float>(FIXED_TIMESTEP) / 1000.0f;
	player->handleEvents(keyboardState, deltaTime);
}

void Game::update() {
	// Update game objects here
	player->update();
	for (auto bullet : player->getBullets()) {
		bullet->update();
	}
	for (auto it = enemies.begin(); it != enemies.end(); ) {
		auto enemy = *it;
		enemy->update();

		for (auto bullet : enemy->getBullets()) {
			bullet->update();
		}

		// Check for collision between player and enemy
		if (checkCollision(player->getBoundingBox(), enemy->getBoundingBox())) {
			// Handle collision
			std::cout << "Collision detected!" << std::endl;
		}

		// Check for collision between bullets and enemy
		for (auto bullet : player->getBullets()) {
			if (checkCollision(bullet->getBoundingBox(), enemy->getBoundingBox())) {
				// Handle bullet-enemy collision
				std::cout << "Bullet hit enemy!" << std::endl;
				bullet->hitEnemy = true;
				enemy->takeDamage(1);
			}
		}

		if (enemy->getHealth() <= 0) {
			Explosion* explosion = new Explosion(renderer, enemy->getX(), enemy->getY(), this->explosionImagePaths);
			explosions.push_back(explosion);
			it = enemies.erase(it);
			delete enemy;
		}
		else {
			++it;
		}
	}
	for (auto it = explosions.begin(); it != explosions.end();) {
		(*it)->update();

		if ((*it)->isFinished()) {
			delete* it;
			it = explosions.erase(it);
		}
		else {
			++it;
		}
	}
}

void Game::render(float interpolation) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Render game background
	SDL_Rect backgroundSrcRect = { 0, 0, 800, 600 }; 
	SDL_Rect backgroundDestRect = { 0, 0, 800, 600 };
	SDL_RenderCopy(renderer, backgroundTexture, &backgroundSrcRect, &backgroundDestRect);


	// Render game objects here
	player->render(renderer, interpolation);

	for (auto bullet : player->getBullets()) {
		bullet->render(renderer);
	}

	for (auto explosion : explosions) {
		explosion->render();
	}

	// Render all enemies
	for (auto enemy : enemies) {
		enemy->render(renderer);
		for (auto bullet : enemy->getBullets()) {
			bullet->render(renderer);
		}
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player;
	for (auto enemy : enemies) {
		delete enemy;
	}
	for (auto explosion : explosions) {
		delete explosion;
	}
	explosions.clear();
	explosionImagePaths.clear();
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool Game::isRunning() {
	return running;
}

bool Game::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
	return SDL_HasIntersection(&a, &b) == SDL_TRUE;
}