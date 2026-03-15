#include "Game.hpp"

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
}
Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
		std::cout << "Subsystems Initialized!..." << std::endl; 
		
		window = SDL_CreateWindow(title, width, height, flags);

		if(window) {
			std::cout << "Window created!" << std::endl;
			renderer = SDL_CreateRenderer(window, nullptr);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
		}
		
	}
	else {
		isRunning = false;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) { 
		switch (event.type) {
		case SDL_EVENT_QUIT:
			isRunning = false;
			break;
		}
	}
}



void Game::update()
{
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//stuff to render:

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
	
}


