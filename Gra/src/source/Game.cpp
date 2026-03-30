#include "../include/Game.hpp"
#include "../include/GameStats.hpp"
#include<string>
std::unique_ptr<GameStats> GStats = std::make_unique<GameStats>();
SDL_Texture* BigYahulTex = nullptr;
SDL_Texture* PlayButtonTex = nullptr;

Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), 
isFullscreen(false), lastTime(0), deltaTime(0.0f), font(nullptr), MainClicker{ 0.0f, 0.0f, 0.0f, 0.0f }
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
				SDL_SetRenderVSync(renderer, 0);
				LOG("Renderer created!");
				SDL_RenderClear(renderer);

			}
			SDL_SetWindowMinimumSize(window, 1200, 900);
		isRunning = true;
		}
		SDL_Surface* IconSurface = IMG_Load("assets/images/BigYahul.png");
		SDL_SetWindowIcon(window, IconSurface);
		SDL_DestroySurface(IconSurface);
		PlayButtonTex = IMG_LoadTexture(renderer, "assets/play_button/play_button1.png");
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
				{//play button click
					if (event.button.x >= PlayButtonRect.x &&
						event.button.x <= PlayButtonRect.x + PlayButtonRect.w &&
						event.button.y >= PlayButtonRect.y &&
						event.button.y <= PlayButtonRect.y + PlayButtonRect.h) {
						LOG("Play Button clicked!");
						SDL_DestroyTexture(PlayButtonTex);
						SDL_Delay(200);
						for(int i = 1; i <=8; i++) {
							SDL_Texture* tempTex = IMG_LoadTexture(renderer, ("assets/play_button/play_button" + std::to_string(i) + ".png").c_str());
							SDL_RenderClear(renderer);
							SDL_SetTextureScaleMode(tempTex, SDL_SCALEMODE_PIXELART);
							SDL_RenderTexture(renderer, tempTex, nullptr, nullptr);
							SDL_RenderPresent(renderer);
							SDL_DestroyTexture(tempTex);
							SDL_Delay(100);
						}// after animation load main menu 
						
						BigYahulTex = IMG_LoadTexture(renderer, "assets/images/BigYahul.png");

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
					// Handle escape key press and pause button (pause game and open game menu);
			default:
					break;
			}
			break;
		}
	}
}



void Game::update()
{ 
	{
		//delta time;
		Uint64 currentTime = SDL_GetTicksNS();
		deltaTime = (currentTime - lastTime) / 1000000000.0f;
		lastTime = currentTime;
	}
	{
		//stars counter update
		unsigned long long stars = GStats->GetStars();
		if (stars != previousStars) {
			LOG("Stars: " << stars);
			previousStars = stars;
		}
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	//stuff to render:
	int width, height;
	SDL_GetRenderOutputSize(renderer, &width, &height);
	{//fps counter
		SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
		SDL_RenderDebugTextFormat(renderer, 50, 10, "FPS: %.2f", 1.0f / deltaTime);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	

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
	{ // play button
		float PlayButtonTexW, PlayButtonTexH;
		SDL_GetTextureSize(PlayButtonTex, &PlayButtonTexW, &PlayButtonTexH);
		float aspectRatio = PlayButtonTexW / PlayButtonTexH;
		PlayButtonRect.w = width / 6;
		PlayButtonRect.h = PlayButtonRect.w / aspectRatio;
		if (PlayButtonRect.h > height) {
			PlayButtonRect.h = height;
			PlayButtonRect.w = PlayButtonRect.h * aspectRatio;
		}
		PlayButtonRect.x = (width - PlayButtonRect.w) / 2;
		PlayButtonRect.y = (height - PlayButtonRect.h) / 2;
		SDL_SetTextureScaleMode(PlayButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, PlayButtonTex, nullptr, &PlayButtonRect);
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyTexture(BigYahulTex);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();
	LOG("Game Cleaned!");
}


