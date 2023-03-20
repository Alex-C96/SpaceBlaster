#include "Game.h"
#include "Player.h"
#include "SDL_image.h"
#include <iostream>

Game::Game() : running(false), window(nullptr), renderer(nullptr), player(nullptr) {}

Game::~Game() {}

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

	player = new Player(renderer);

	running = true;
	return true;
}

void Game::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				running = false;
				break;
			default:
				player->handleEvents(event);
				break;
		}
	}
}

void Game::update() {
	// Update game objects here
	player->update();
}

void Game::render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// Render game objects here
	player->render(renderer);

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	delete player;
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

bool Game::isRunning() {
	return running;
}