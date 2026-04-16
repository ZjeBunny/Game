#include "../../include/ui/GameMenu.hpp"

const std::string SavePath = "src/save/GameSave.db";

void Menu::LoadMenuAssets(SDL_Renderer* renderer, int windowW, int windowH)
{
	cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	cursorDefault = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
	MenuBackgroundTex = IMG_LoadTexture(renderer, "assets/menu_background.png");


	MenuTitleTex = IMG_LoadTexture(renderer, "assets/menu_title.png");
	MenuTitleRect = Helper::CalculateRectCenter(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);


	NewGameButtonTex = IMG_LoadTexture(renderer, "assets/new_game/new_game6.png");
	NewGameButtonRect = Helper::CalculateRectCenter(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f,false);


	ContinueButtonTex = IMG_LoadTexture(renderer, "assets/continue/continue7.png");
	ContinueButtonRect = Helper::CalculateRectCenter(ContinueButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f,false);


	SettingsButtonTex = IMG_LoadTexture(renderer, "assets/settings_button/settings6.png");
	SettingsButtonRect = Helper::CalculateRectCenter(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f,false);


	ExitButtonTex = IMG_LoadTexture(renderer, "assets/exit/exit6.png");
	ExitButtonRect = Helper::CalculateRectCenter(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f,false);

	font = TTF_OpenFont("assets/fonts/ThaleahFat.ttf", 48.0f);

	PromptBackgroundTex = IMG_LoadTexture(renderer, "assets/item/item_background.png");
	PromptBackgroundRect = Helper::CalculateRect(PromptBackgroundTex, 0.5f, 0.3f, windowW, windowH, 0.5f, 0.5f, true);

	SDL_Surface* newGameTextQuestionSurface = TTF_RenderText_Solid(font, newGameTextQuestion, 0, { 1,0, 66, 255 });
	SDL_Surface* newGameTextWarningSurface = TTF_RenderText_Solid(font, newGameTextWarning, 0, { 1,0, 66, 255 });
	SDL_Surface* newGameTextYesSurface = TTF_RenderText_Solid(font, newGameTextYes, 0, { 255, 0, 0, 255 });
	SDL_Surface* newGameTextNoSurface = TTF_RenderText_Solid(font, newGameTextNo, 0, { 0, 255, 0, 255 });

	newGameTextQuestionTex = SDL_CreateTextureFromSurface(renderer, newGameTextQuestionSurface);
	newGameTextWarningTex = SDL_CreateTextureFromSurface(renderer, newGameTextWarningSurface);
	newGameTextYesTex = SDL_CreateTextureFromSurface(renderer, newGameTextYesSurface);
	newGameTextNoTex = SDL_CreateTextureFromSurface(renderer, newGameTextNoSurface);

	PromptBackgroundRect = Helper::CalculateRectCenter(PromptBackgroundTex, 0.5f, 0.4f, windowW, windowH, 0.3f, true);
	newGameTextQuestionRect = Helper::CalculateRectCenter(newGameTextQuestionTex, 0.4f, 0.05f, windowW, windowH, 0.35f, true);
	newGameTextWarningRect = Helper::CalculateRectCenter(newGameTextWarningTex, 0.4f, 0.05f, windowW, windowH, 0.40f, true);

	newGameTextYesRect = { PromptBackgroundRect.x + 100, PromptBackgroundRect.y + 200, 200, 100 };
	newGameTextNoRect = { PromptBackgroundRect.x + PromptBackgroundRect.w - 300, PromptBackgroundRect.y + 200, 200, 100 };

	NewGameButtonRect_Base = NewGameButtonRect;
	ContinueButtonRect_Base = ContinueButtonRect;
	SettingsButtonRect_Base = SettingsButtonRect;
	ExitButtonRect_Base = ExitButtonRect;
	newGameTextYesRect_Base = newGameTextYesRect;
	newGameTextNoRect_Base = newGameTextNoRect;


	SDL_DestroySurface(newGameTextQuestionSurface);
	SDL_DestroySurface(newGameTextWarningSurface);
	SDL_DestroySurface(newGameTextYesSurface);
	SDL_DestroySurface(newGameTextNoSurface);
}
void Menu::RenderMenu(SDL_Renderer* renderer)
{
	float mX, mY;
	SDL_GetMouseState(&mX, &mY);
	SDL_FPoint mousePos = { mX, mY };

	HoverEffect(&NewGameButtonRect, NewGameButtonRect_Base, mousePos);
	HoverEffect(&ContinueButtonRect, ContinueButtonRect_Base, mousePos);
	HoverEffect(&SettingsButtonRect, SettingsButtonRect_Base, mousePos);
	HoverEffect(&ExitButtonRect, ExitButtonRect_Base, mousePos);
	if (MenuBackgroundTex) {
		SDL_SetTextureScaleMode(MenuBackgroundTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, MenuBackgroundTex, nullptr, nullptr);
	}
	if (MenuTitleTex) {
		SDL_SetTextureScaleMode(MenuTitleTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, MenuTitleTex, nullptr, &MenuTitleRect);
	}
	if (ContinueButtonTex) {
		if (Helper::SaveExists(SavePath)) {
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
	MenuTitleRect = Helper::CalculateRectCenter(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);

	NewGameButtonRect = Helper::CalculateRectCenter(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f, false);
	ContinueButtonRect = Helper::CalculateRectCenter(ContinueButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f, false);
	SettingsButtonRect = Helper::CalculateRectCenter(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f, false);
	ExitButtonRect = Helper::CalculateRectCenter(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f, false);

	NewGameButtonRect_Base = NewGameButtonRect;
	ContinueButtonRect_Base = ContinueButtonRect;
	SettingsButtonRect_Base = SettingsButtonRect;
	ExitButtonRect_Base = ExitButtonRect;

	PromptBackgroundRect = Helper::CalculateRectCenter(PromptBackgroundTex, 0.5f, 0.4f, windowW, windowH, 0.3f, true);
	newGameTextQuestionRect = Helper::CalculateRectCenter(newGameTextQuestionTex, 0.4f, 0.05f, windowW, windowH, 0.35f, true);
	newGameTextWarningRect = Helper::CalculateRectCenter(newGameTextWarningTex, 0.4f, 0.05f, windowW, windowH, 0.40f, true);

	newGameTextYesRect = { PromptBackgroundRect.x + 100, PromptBackgroundRect.y + 200, 200, 100 };
	newGameTextNoRect = { PromptBackgroundRect.x + PromptBackgroundRect.w - 300, PromptBackgroundRect.y + 200, 200, 100 };

	newGameTextYesRect_Base = newGameTextYesRect;
	newGameTextNoRect_Base = newGameTextNoRect;
}
void Menu::HandleMenuEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer)
{
		int winW, winH;
		SDL_GetRenderOutputSize(renderer, &winW, &winH);
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_EVENT_WINDOW_RESIZED) {
			 winW = event.window.data1;
			 winH = event.window.data2;
			UpdateLayout(winW, winH);
		}
		if (event.type == SDL_EVENT_MOUSE_MOTION) {
			SDL_FPoint mousePos = { event.motion.x, event.motion.y };
			
			bool isOverAnyButton = SDL_PointInRectFloat(&mousePos, &NewGameButtonRect_Base) ||
				(SDL_PointInRectFloat(&mousePos, &ContinueButtonRect_Base) && Helper::SaveExists(SavePath)) ||
				SDL_PointInRectFloat(&mousePos, &SettingsButtonRect_Base) ||
				SDL_PointInRectFloat(&mousePos, &ExitButtonRect_Base);

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
					if (!Helper::SaveExists(SavePath)) {
						RunAnimation(renderer, NewGameButtonTex, "assets/new_game/new_game", 6, 100);
						currentState = GameState::PLAYING;
					}
					else {
						RunAnimation(renderer, NewGameButtonTex, "assets/new_game/new_game", 6, 100);
						if (NewGamePrompt(renderer, winW, winH, this->font, event)) {
							currentState = GameState::PLAYING;
						}
						else {
							this->RenderMenu(renderer);
						}
					}
				}
				//Continue Button
				if(SDL_PointInRectFloat(&mousePos, &ContinueButtonRect) && Helper::SaveExists("src/save/GameSave.db"	)) {
					LOG("Pressed Continue Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					RunAnimation(renderer, ContinueButtonTex, "assets/continue/continue", 7, 100);
				}
				//Settings Button
				if(SDL_PointInRectFloat(&mousePos, &SettingsButtonRect)) {
					LOG("Pressed Settings Button");
					SDL_SetCursor(SDL_GetDefaultCursor());
					RunAnimation(renderer, SettingsButtonTex, "assets/settings_button/settings", 6, 100);
					currentState = GameState::SETTINGS;
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

	SDL_DestroyTexture(newGameTextQuestionTex);
	SDL_DestroyTexture(newGameTextWarningTex);
	SDL_DestroyTexture(newGameTextYesTex);
	SDL_DestroyTexture(newGameTextNoTex);

	TTF_CloseFont(font);
}

inline void Menu::RunAnimation(SDL_Renderer* renderer, SDL_Texture*& TexName, const std::string& TexPath, int AmmountOfFrames, int delayMS) 
{
	SDL_Texture* originalTex = TexName;
	for (int i = AmmountOfFrames; i >= 1; i--) {
		std::string path = TexPath + std::to_string(i) + ".png";
		SDL_Texture* tempTex = IMG_LoadTexture(renderer, path.c_str());

		if (tempTex) {
			TexName = tempTex;
			SDL_RenderClear(renderer);
			this->RenderMenu(renderer);
			SDL_RenderPresent(renderer);
			SDL_Delay(delayMS);
			SDL_DestroyTexture(tempTex); 
		}
	}

	TexName = originalTex;
	SDL_RenderClear(renderer);
	this->RenderMenu(renderer);
	SDL_RenderPresent(renderer);
}

inline void Menu::HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos) {
	if (SDL_PointInRectFloat(&mousePos, &baseRect)) {
		currentRect->w = baseRect.w * 1.1f;
		currentRect->h = baseRect.h * 1.1f;
		currentRect->x = baseRect.x - (currentRect->w - baseRect.w) / 2.0f;
		currentRect->y = baseRect.y - (currentRect->h - baseRect.h) / 2.0f;
	}
	else {
		*currentRect = baseRect;
	}
}

bool Menu::NewGamePrompt(SDL_Renderer* renderer, int windowW, int windowH, TTF_Font* font, SDL_Event& event) {
	PromptBackgroundRect = Helper::CalculateRectCenter(PromptBackgroundTex, 0.5f, 0.4f, windowW, windowH, 0.3f, true);
	newGameTextQuestionRect = Helper::CalculateRectCenter(newGameTextQuestionTex, 0.4f, 0.05f, windowW, windowH, 0.35f, true);
	newGameTextWarningRect = Helper::CalculateRectCenter(newGameTextWarningTex, 0.4f, 0.05f, windowW, windowH, 0.40f, true);

	newGameTextYesRect = { PromptBackgroundRect.x + 100, PromptBackgroundRect.y + 200, 200, 100 };
	newGameTextNoRect = { PromptBackgroundRect.x + PromptBackgroundRect.w - 300, PromptBackgroundRect.y + 200, 200, 100 };
	newGameTextYesRect_Base = newGameTextYesRect;
	newGameTextNoRect_Base = newGameTextNoRect;
	bool answer = false;
	bool continueLoop = true;
	while (continueLoop) {
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_MOUSE_MOTION) {
				SDL_FPoint mousePos = { event.motion.x, event.motion.y };

				bool isOverAnyButton =  SDL_PointInRectFloat(&mousePos, &newGameTextYesRect)
					|| SDL_PointInRectFloat(&mousePos, &newGameTextNoRect);

				if (isOverAnyButton) {
					SDL_SetCursor(cursorPointer);
				}
				else {
					SDL_SetCursor(SDL_GetDefaultCursor());
				}
				HoverEffect(&newGameTextNoRect, newGameTextNoRect_Base, mousePos);
				HoverEffect(&newGameTextYesRect, newGameTextYesRect_Base, mousePos);
			}
			if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
				SDL_FPoint mousePos = { event.button.x, event.button.y };
				if (SDL_PointInRectFloat(&mousePos, &newGameTextYesRect)) {
					SDL_SetCursor(SDL_GetDefaultCursor());
					answer = true;
					continueLoop = false;
					break;
				}
				if (SDL_PointInRectFloat(&mousePos, &newGameTextNoRect)) {
					SDL_SetCursor(SDL_GetDefaultCursor());
					answer = false;
					continueLoop = false;
					this->RenderMenu(renderer);
					break;
				}
			}
		}
		SDL_RenderClear(renderer);
		this->RenderMenu(renderer); 
		SDL_SetTextureScaleMode(PromptBackgroundTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, PromptBackgroundTex, nullptr, &PromptBackgroundRect);
		SDL_RenderTexture(renderer, newGameTextQuestionTex, nullptr, &newGameTextQuestionRect);
		SDL_RenderTexture(renderer, newGameTextWarningTex, nullptr, &newGameTextWarningRect);
		SDL_RenderTexture(renderer, newGameTextYesTex, nullptr, &newGameTextYesRect);
		SDL_RenderTexture(renderer, newGameTextNoTex, nullptr, &newGameTextNoRect);

		SDL_RenderPresent(renderer);
	}
	return answer;
}
