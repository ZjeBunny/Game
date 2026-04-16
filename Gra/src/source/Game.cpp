#include "../include/Game.hpp"
#include<string>
const char* DBPath = "./src/save/GameSave.db";
SDL_Texture* PlayButtonTex = nullptr;
std::unique_ptr<Menu> gameMenu = std::make_unique<Menu>();
std::unique_ptr<Main> gameMain = std::make_unique<Main>();
std::unique_ptr<GSettings> gameSettings = std::make_unique<GSettings>();

Game::Game() : isRunning(false), window(nullptr), windowHeight(0), windowWidth(0), renderer(nullptr), isFullscreen(false),
fpsCounter(false), lastTime(0), deltaTime(0.0f), currentState(GameState::START_SCREEN), font(nullptr), PlayButtonRect{ 0, 0, 0, 0 }
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
			SDL_GetWindowSize(window, &windowWidth, &windowHeight);
			SDL_WarpMouseInWindow(window, windowWidth / 2.0f, windowHeight / 2.0f);
			renderer = SDL_CreateRenderer(window, nullptr);
			if (renderer) {
				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_SetRenderVSync(renderer, 0);
				LOG("Renderer created!");
				SDL_RenderClear(renderer);
				TTF_Init();
				font = TTF_OpenFont("assets/fonts/ThaleahFat.ttf", 48.0f);
			}
			SDL_SetWindowMinimumSize(window, 1280, 960);
		isRunning = true;
		}
		SDL_Surface* IconSurface = IMG_Load("assets/images/BigYahul.png");
		SDL_SetWindowIcon(window, IconSurface);
		SDL_DestroySurface(IconSurface);
		
		PlayButtonTex = IMG_LoadTexture(renderer, "assets/play_button/play_button1.png");
		cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
		cursorDefault = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);

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
			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_FPoint mousePos = { event.motion.x, event.motion.y };
				if(SDL_PointInRectFloat(&mousePos, &PlayButtonRect)) {
					SDL_SetCursor(cursorPointer);
				}
				else {
					SDL_SetCursor(cursorDefault);
				}
			}
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				if (event.button.button == SDL_BUTTON_LEFT) {
					float mouseX = event.button.x;
					float mouseY = event.button.y;

					if (mouseX >= PlayButtonRect.x && mouseX <= PlayButtonRect.x + PlayButtonRect.w &&
						mouseY >= PlayButtonRect.y && mouseY <= PlayButtonRect.y + PlayButtonRect.h) {
						SDL_SetCursor(cursorDefault);
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
		{
			GameState stateBefore = currentState;
			gameMenu->HandleMenuEvents(event, isRunning, currentState, renderer);
			if (stateBefore == GameState::MENU && currentState == GameState::SETTINGS) {
				gameSettings->LoadSettingsAssets(renderer, windowWidth, windowHeight);
			}
			else if (stateBefore == GameState::MENU && currentState == GameState::PLAYING) {
				gameMenu->CleanMenu();
				gameMain->LoadMainAssets(renderer, windowWidth, windowHeight);
			}
			break;
		}
		case GameState::PLAYING:
			gameMain->HandleMainEvents(event, isRunning, currentState, renderer);
			break;
		case GameState::SETTINGS:
			gameSettings->HandleSettingsEvents(event, isRunning, currentState, renderer);
			break;
		}
		
		

		if (event.type == SDL_EVENT_KEY_DOWN) {
			if (event.key.key == SDLK_F11) {
				isFullscreen = !isFullscreen;
				SDL_SetWindowFullscreen(window, isFullscreen ? SDL_WINDOW_FULLSCREEN : 0);
				if (!isFullscreen) SDL_MaximizeWindow(window);
				int w, h;
				SDL_GetWindowSize(window, &w, &h);
				gameMenu->UpdateLayout(w, h);
				gameMain->UpdateLayout(w, h);
			}
		}
	}
	int w, h;
	SDL_GetRenderOutputSize(renderer, &w, &h);

	switch (currentState) {
	case GameState::MENU:
		gameMenu->UpdateLayout(w, h);
		break;
	case GameState::PLAYING:
		gameMain->UpdateLayout(w, h);
		break;
	case GameState::SETTINGS:
		gameSettings->UpdateLayout(w, h);
		break;
	}
}




void Game::update()
{ 
		Uint64 currentTime = SDL_GetTicksNS();
		deltaTime = (currentTime - lastTime) / 1000000000.0f;
		lastTime = currentTime;
		switch (currentState)
		{

		case GameState::PLAYING:
			gameMain->Update(renderer);
			break;
		default:
			break;
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

				SDL_Surface* textStart = TTF_RenderText_Solid(font, "Click to Start!", 0, { 255, 255, 255, 255 });
				if (textStart) {
					SDL_Texture* textTex = SDL_CreateTextureFromSurface(renderer, textStart);

					SDL_FRect destRect = {
						(windowWidth - textStart->w) / 2.0f,
						PlayButtonRect.y - textStart->h - 100,
						(float)textStart->w,
						(float)textStart->h
					};
					SDL_RenderTexture(renderer, textTex, nullptr, &destRect);
					SDL_DestroyTexture(textTex);
					SDL_DestroySurface(textStart);
				}
			}
			break;
		case GameState::MENU:
			gameMenu->RenderMenu(renderer);
			break;
		case GameState::PLAYING:
			gameMain->RenderMain(renderer);
			break;
		case GameState::PAUSED:
			// Render paused screen here
			break;
		case GameState::SETTINGS:
			gameSettings->RenderSettings(renderer);
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
