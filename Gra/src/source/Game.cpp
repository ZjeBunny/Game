#include "../include/Game.hpp"


SDL_Texture* BigYahulTex = nullptr;


Game::Game() : isRunning(false), window(nullptr), renderer(nullptr)
{
}
Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags += SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO)) {
		LOG("Subsystems Initialized!...");
		
		window = SDL_CreateWindow(title, width, height, flags);

		if(window) {
			LOG("Window created!");
			renderer = SDL_CreateRenderer(window, nullptr);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			LOG("Renderer created!");
		}
		isRunning = true;
		}
		
		BigYahulTex = IMG_LoadTexture(renderer, "assets/BigYahul.png");
		
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
				LOG("Left mouse button clicked at (" << event.button.x << ", " << event.button.y << ")");
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
	SDL_GetTextureSize(BigYahulTex, &spriteRect.w, &spriteRect.h);
	spriteRect.x = (width - spriteRect.w) / 2;
	spriteRect.y = (height - spriteRect.h) / 2;

	SDL_RenderTexture(renderer, BigYahulTex, nullptr, &spriteRect);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyTexture(BigYahulTex);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	LOG("Game Cleaned!");
	
}


