#include "../include/Game.hpp"
#include<string>

std::unique_ptr<GameSave> gameState = std::make_unique<GameSave>();
const char* DBPath = "./src/save/GameSave.db";
SDL_Texture* PlayButtonTex = nullptr;
std::unique_ptr<Menu> gameMenu = std::make_unique<Menu>();


Game::Game() : isRunning(false), window(nullptr), renderer(nullptr), 
isFullscreen(false), lastTime(0), deltaTime(0.0f), font(nullptr), fpsCounter(false), windowHeight(0), windowWidth(0), 
PlayButtonRect{ 0, 0, 0, 0 }, currentState(GameState::START_SCREEN)
{
}


void Game::init(const char* title, int width, int height, bool fullscreen, bool maximizeWindow)
{	
	windowWidth = width;
	windowHeight = height;
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
				TTF_Init();
				font = TTF_OpenFont("assets/fonts/ThaleahFat.ttf", 48.0f);
			}
			SDL_SetWindowMinimumSize(window, 1200, 900);
		isRunning = true;
		}
		gameState->createDB(DBPath);
		gameState->createTableSaves(DBPath);
		gameState->createTableUpgrades(DBPath);
		gameState->createSettingsTable(DBPath);
		gameState->createSaveFile(DBPath, "Game Save");

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

		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
			return;
		}

		switch (currentState) {
		case GameState::START_SCREEN:
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					float mouseX = event.button.x;
					float mouseY = event.button.y;

					if (mouseX >= PlayButtonRect.x && mouseX <= PlayButtonRect.x + PlayButtonRect.w &&
						mouseY >= PlayButtonRect.y && mouseY <= PlayButtonRect.y + PlayButtonRect.h) {

						LOG("Play Button clicked!");

						// Animacja
						for (int i = 1; i <= 8; i++) {
							SDL_Texture* tempTex = IMG_LoadTexture(renderer, ("assets/play_button/play_button" + std::to_string(i) + ".png").c_str());
							SDL_RenderClear(renderer);
							SDL_SetTextureScaleMode(tempTex, SDL_SCALEMODE_PIXELART);
							SDL_RenderTexture(renderer, tempTex, nullptr, nullptr);
							SDL_RenderPresent(renderer);
							SDL_DestroyTexture(tempTex);
							SDL_Delay(100);
						}

						gameMenu->LoadMenuAssets(renderer, windowWidth, windowHeight);
						currentState = GameState::MENU;

						SDL_DestroyTexture(PlayButtonTex);
						PlayButtonTex = nullptr;
					}
				}
			}
			break;

		case GameState::MENU:
			gameMenu->HandleMenuEvents(event, isRunning, currentState);
			break;
		}

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_F11) {
				isFullscreen = !isFullscreen;
				SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
				if (!isFullscreen) SDL_MaximizeWindow(window);
			}
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

	}
}

void Game::render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	int windowWidth, windowHeight;
	SDL_GetRenderOutputSize(renderer, &windowWidth, &windowHeight);


	// FPS Counter
	if (fpsCounter) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDebugTextFormat(renderer, 50, 10, "FPS: %.2f", 1.0f / deltaTime);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}
	
	switch (currentState)
	{
		case GameState::START_SCREEN:
			if (PlayButtonTex) {
				float texW, texH;
				SDL_GetTextureSize(PlayButtonTex, &texW, &texH);
				float aspectRatio = texH / texW;
				PlayButtonRect.w = windowWidth * 0.2f;
				PlayButtonRect.h = PlayButtonRect.w * aspectRatio;

				PlayButtonRect.x = (windowWidth - PlayButtonRect.w) / 2.0f;
				PlayButtonRect.y = (windowHeight - PlayButtonRect.h) / 2.0f;
				SDL_SetTextureScaleMode(PlayButtonTex, SDL_SCALEMODE_PIXELART);
				SDL_RenderTexture(renderer, PlayButtonTex, nullptr, &PlayButtonRect);
			}
			break;
		case GameState::MENU:
			gameMenu->RenderMenu(renderer);
			break;
		case GameState::PLAYING:
			// Render game elements here
			break;
		case GameState::PAUSED:
			// Render paused screen here
			break;
		case GameState::SETTINGS:
			// Render settings screen here
			break;
		
	}


	SDL_RenderPresent(renderer);
}


void Game::clean()
{
	SDL_DestroyRenderer(renderer);
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_Quit();
	LOG("Game Cleaned!");
}


//SDL_Surface* TTF_Surface = TTF_RenderText_Solid(font, "test text", 0, { 255, 255, 255, 255 });
//textTex = SDL_CreateTextureFromSurface(renderer, TTF_Surface);
//destRect = { 50, 50, (float)TTF_Surface->w, (float)TTF_Surface->h };
//SDL_DestroySurface(TTF_Surface);