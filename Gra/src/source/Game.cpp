#include "../include/Game.hpp"
#include "../include/GameStats.hpp"

GameStats* stats = nullptr;


SDL_Texture* BigYahulTex = nullptr;


Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), isFullscreen(false)
{
}
Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen)
{	
	isFullscreen = fullscreen;
	int flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO) == 1) {
		LOG("Subsystems Initialized!...");
		
		window = SDL_CreateWindow(title, width, height, flags);
		if (!isFullscreen) SDL_MaximizeWindow(window);
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
		case SDL_EVENT_KEY_DOWN:
			LOG("Key pressed: %s", SDL_GetKeyName(event.key.key));
			if (event.key.key == SDLK_F11) {
				isFullscreen = !isFullscreen;

				if (isFullscreen) 
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
				else 
					SDL_SetWindowFullscreen(window, 0);
					SDL_MaximizeWindow(window);
			}
			if (event.key.key == SDLK_ESCAPE) {
				
				
			}
			break;
		
		}
		
	}
}



void Game::update()
{ 
	
	stats = new GameStats;

	unsigned long long stars = stats->GetStars();


}

void Game::render()
{
	SDL_RenderClear(renderer);
	//atuff to render:
	SDL_FRect dstrect;
	int width = 0, height = 0;
	SDL_GetRenderOutputSize(renderer, &width, &height);
	SDL_GetTextureSize(BigYahulTex, &dstrect.w, &dstrect.h);
	dstrect.x = (width - dstrect.w) / 16;
	dstrect.y = (height - dstrect.h) / 16;


	SDL_RenderTexture(renderer, BigYahulTex, nullptr , &dstrect);
	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(BigYahulTex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	LOG("Game Cleaned!");
}


