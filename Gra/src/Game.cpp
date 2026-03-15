#include "Game.hpp"

SDL_Texture *BigYahul = nullptr;

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

	if (SDL_Init(SDL_INIT_VIDEO)) {
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
		BigYahul = IMG_LoadTexture(renderer, "assets/BigYahul.png");
		
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
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				std::cout << "Left mouse button clicked at (" << event.button.x << ", " << event.button.y << ")" << std::endl;
			}
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
	SDL_FRect spriteRect;
	int width = 0, height = 0;
	SDL_GetRenderOutputSize(renderer, &width, &height);
	SDL_GetTextureSize(BigYahul, &spriteRect.w, &spriteRect.h);
	spriteRect.x = (width - spriteRect.w) / 2;
	spriteRect.y = (height - spriteRect.h) / 2;

	SDL_RenderTexture(renderer, BigYahul, nullptr, &spriteRect);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(BigYahul);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Cleaned!" << std::endl;
	
}


