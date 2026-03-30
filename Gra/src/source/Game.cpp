#include "../include/Game.hpp"
#include "../include/GameStats.hpp"


std::unique_ptr<GameStats> GStats = std::make_unique<GameStats>();
SDL_Texture* BigYahulTex = nullptr;


Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), 
isFullscreen(false), lastTime(0), deltaTime(0.0f), font(nullptr), MainClicker{ 0.0f, 0.0f, 0.0f, 0.0f }
{
}
Game::~Game()
{
}

void Game::init(const char* title, int width, int height, bool fullscreen, bool maximizeWindow)
{	
	isFullscreen = fullscreen;
	int flags = SDL_WINDOW_RESIZABLE;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_VIDEO)) {
		LOG("Subsystems Initialized!...");
		
		window = SDL_CreateWindow(title, width, height, flags);
		if (!isFullscreen && maximizeWindow) SDL_MaximizeWindow(window);
		if(window) {
			LOG("Window created!");
			renderer = SDL_CreateRenderer(window, nullptr);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				LOG("Renderer created!");
			}
			SDL_SetWindowMinimumSize(window, 1200, 900);
		isRunning = true;
		}
		BigYahulTex = IMG_LoadTexture(renderer, "assets/images/BigYahul.png");
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

				{	//Handle click on main clicker
					if (event.button.x >= MainClicker.x &&
						event.button.x <= MainClicker.x + MainClicker.w &&
						event.button.y >= MainClicker.y &&
						event.button.y <= MainClicker.y + MainClicker.h) {
						LOG("Main Clicker clicked!");
						GStats->GameIcremeantStars();
					}
				}
			}
			break;
		case SDL_EVENT_KEY_DOWN:
			LOG("Key pressed: " << SDL_GetKeyName(event.key.key));
			switch (event.key.key)
			{
			case SDLK_F11:
				isFullscreen = !isFullscreen;

				if (isFullscreen)
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
				else
					SDL_SetWindowFullscreen(window, 0);
					SDL_MaximizeWindow(window);
				break;
			case SDLK_ESCAPE:
					// Handle escape key press(pause game and open game menu);
			default:
					break;
			}
			break;
		}
	}
}



void Game::update()
{ 
	//delta time for animations to look same on different hardware;
	Uint64 currentTime = SDL_GetTicks();
	deltaTime = (currentTime - lastTime) / 1000.0f;
	if (deltaTime > 0.1f) deltaTime = 0.1f;
	lastTime = currentTime;
	unsigned long long stars = GStats->GetStars();
	LOG("Stars: " << stars);
}

void Game::render()
{
	SDL_RenderClear(renderer);
	//atuff to render:
	int width, height;
	SDL_GetRenderOutputSize(renderer, &width, &height);
	
	{// Generetaning main clicking texture and rendering it to the center of the screen
		float MainClickerTexW, MainClickerTexH;
		SDL_GetTextureSize(BigYahulTex, &MainClickerTexW, &MainClickerTexH);
		float aspectRatio = MainClickerTexW / MainClickerTexH;

		MainClicker.w = width / 4;
		MainClicker.h = MainClicker.w / aspectRatio;
		if (MainClicker.h > height) {
			MainClicker.h = height;
			MainClicker.w = MainClicker.h * aspectRatio;
		}
		MainClicker.x = (width - MainClicker.w) / 2;
		MainClicker.y = (height - MainClicker.h) / 2;
		SDL_RenderTexture(renderer, BigYahulTex, nullptr, &MainClicker);
	}
	

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(BigYahulTex);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_DestroyWindow(window);
	GStats.reset();
	SDL_Quit();
	LOG("Game Cleaned!");
}


