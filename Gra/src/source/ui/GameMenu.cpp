#include "../../include/ui/GameMenu.hpp"
#include "../../include/Helpers.cpp"

void Menu::LoadMenuAssets(SDL_Renderer* renderer, int windowW, int windowH)
{
	cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	cursorDefault = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
	MenuBackgroundTex = IMG_LoadTexture(renderer, "assets/menu_background.png");


	MenuTitleTex = IMG_LoadTexture(renderer, "assets/menu_title.png");
	MenuTitleRect = CalculateRectCenter(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);


	NewGameButtonTex = IMG_LoadTexture(renderer, "assets/new_game/new_game6.png");
	NewGameButtonRect = CalculateRectCenter(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f,false);


	ContinueButtonTex = IMG_LoadTexture(renderer, "assets/continue/continue7.png");
	ContinueButtonRect = CalculateRectCenter(ContinueButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f,false);


	SettingsButtonTex = IMG_LoadTexture(renderer, "assets/settings_button/settings6.png");
	SettingsButtonRect = CalculateRectCenter(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f,false);


	ExitButtonTex = IMG_LoadTexture(renderer, "assets/exit/exit6.png");
	ExitButtonRect = CalculateRectCenter(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f,false);
}
void Menu::RenderMenu(SDL_Renderer* renderer)
{
	if (MenuBackgroundTex) {
		SDL_SetTextureScaleMode(MenuBackgroundTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, MenuBackgroundTex, nullptr, nullptr);
	}
	if (MenuTitleTex) {
		SDL_SetTextureScaleMode(MenuTitleTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, MenuTitleTex, nullptr, &MenuTitleRect);
	}
	if (ContinueButtonTex) {
		if (SaveExists("src/save/GameSave.db")) {
			SDL_SetTextureScaleMode(ContinueButtonTex, SDL_SCALEMODE_PIXELART);
			SDL_RenderTexture(renderer, ContinueButtonTex, nullptr, &ContinueButtonRect);
		}
		else {
			SDL_SetTextureColorMod(ContinueButtonTex, 128, 128, 128);
			SDL_SetTextureScaleMode(ContinueButtonTex, SDL_SCALEMODE_PIXELART);
			SDL_RenderTexture(renderer, ContinueButtonTex, nullptr, &ContinueButtonRect);
			SDL_SetTextureColorMod(ContinueButtonTex, 255, 255, 255);
		}
	}
	if (NewGameButtonTex) {
		SDL_SetTextureScaleMode(NewGameButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, NewGameButtonTex, nullptr, &NewGameButtonRect);
	}
	if (SettingsButtonTex) {
		SDL_SetTextureScaleMode(SettingsButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, SettingsButtonTex, nullptr, &SettingsButtonRect);
	}
	if (ExitButtonTex) {
		SDL_SetTextureScaleMode(ExitButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, ExitButtonTex, nullptr, &ExitButtonRect);
	}

}

void Menu::UpdateLayout(int windowW, int windowH) {
	MenuTitleRect = CalculateRectCenter(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);
	NewGameButtonRect = CalculateRectCenter(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f, false);
	ContinueButtonRect = CalculateRectCenter(ContinueButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f, false);
	SettingsButtonRect = CalculateRectCenter(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f, false);
	ExitButtonRect = CalculateRectCenter(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f, false);
}

void Menu::HandleMenuEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer)
{
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_EVENT_WINDOW_RESIZED) {
			int newW = event.window.data1;
			int newH = event.window.data2;
			UpdateLayout(newW, newH);
		}
		if (event.type == SDL_EVENT_MOUSE_MOTION) {
			SDL_FPoint mousePos = { event.motion.x, event.motion.y };

			bool isOverAnyButton = SDL_PointInRectFloat(&mousePos, &NewGameButtonRect) ||
				SDL_PointInRectFloat(&mousePos, &ContinueButtonRect) && SaveExists("src/save/GameSave.db") ||
				SDL_PointInRectFloat(&mousePos, &SettingsButtonRect) ||
				SDL_PointInRectFloat(&mousePos, &ExitButtonRect);

			if (isOverAnyButton) {
				SDL_SetCursor(cursorPointer);
			}
			else {
				SDL_SetCursor(SDL_GetDefaultCursor());
			}
			
		}
		if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
			SDL_FPoint mousePos;
			SDL_GetMouseState(&mousePos.x, &mousePos.y);
			if (event.button.button == SDL_BUTTON_LEFT) {
				//New Game Button
				if (SDL_PointInRectFloat(&mousePos, &NewGameButtonRect)) {
					LOG("Pressed New Game Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					if (!SaveExists("src/save/GameSave.db")) {
						RunAnimation(renderer, NewGameButtonTex, "assets/new_game/new_game", 6, 100);
						currentState = GameState::PLAYING;
					}
					else {

					}
				}
				//Continue Button
				if(SDL_PointInRectFloat(&mousePos, &ContinueButtonRect) && SaveExists("src/save/GameSave.db")) {
					LOG("Pressed Continue Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					RunAnimation(renderer, ContinueButtonTex, "assets/continue/continue", 7, 100);
				}
				//Settings Button
				if(SDL_PointInRectFloat(&mousePos, &SettingsButtonRect)) {
					LOG("Pressed Settings Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					RunAnimation(renderer, SettingsButtonTex, "assets/settings_button/settings", 6, 100);
				}
				//Exit Buttonon
				if (SDL_PointInRectFloat(&mousePos, &ExitButtonRect)) {
					LOG("Pressed Exit Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					RunAnimation(renderer, ExitButtonTex, "assets/exit/exit", 6, 100);
					isRunning = false;
				}
			}
			
		}
	}

void Menu::CleanMenu()
{
	SDL_DestroyTexture(MenuBackgroundTex);
	SDL_DestroyTexture(MenuTitleTex);
	SDL_DestroyTexture(NewGameButtonTex);
	SDL_DestroyTexture(ContinueButtonTex);
	SDL_DestroyTexture(SettingsButtonTex);
	SDL_DestroyTexture(ExitButtonTex);
}

inline void Menu::RunAnimation(SDL_Renderer* renderer, SDL_Texture*& TexName, const std::string& TexPath, int AmmountOfFrames, int delayMS) {
	for (AmmountOfFrames; AmmountOfFrames >= 1; AmmountOfFrames--) {
		SDL_DestroyTexture(TexName);
		std::string path = TexPath + std::to_string(AmmountOfFrames) + ".png";
		TexName = IMG_LoadTexture(renderer, path.c_str());
		SDL_RenderClear(renderer);
		this->RenderMenu(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(100);
	}
	SDL_Delay(delayMS);
}