#include "../../include/ui/GameMenu.hpp"
SDL_FRect CalculateRect(SDL_Texture* tex, float widthPercent, float heightPercent, int windowW, int windowH, float yPosPercentage, bool useAspectRatio) {
	float displayW = (float)windowW * widthPercent;
	float displayH;

	if (useAspectRatio && tex) {
		float tw, th;
		SDL_GetTextureSize(tex, &tw, &th);
		float aspect = th / tw;
		displayH = displayW * aspect;
	}
	else {
		displayH = (float)windowH * heightPercent;
	}

	float displayX = (windowW - displayW) / 2.0f;
	float displayY = (float)windowH * yPosPercentage;

	return { displayX, displayY, displayW, displayH };
}

void Menu::LoadMenuAssets(SDL_Renderer* renderer, int windowW, int windowH)
{

	MenuBackgroundTex = IMG_LoadTexture(renderer, "assets/menu_background.png");


	MenuTitleTex = IMG_LoadTexture(renderer, "assets/menu_title.png");
	MenuTitleRect = CalculateRect(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);


	NewGameButtonTex = IMG_LoadTexture(renderer, "assets/new_game/new_game6.png");
	NewGameButtonRect = CalculateRect(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f,false);


	PlayButtonTex = IMG_LoadTexture(renderer, "assets/play/play6.png");
	PlayButtonRect = CalculateRect(PlayButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f,false);


	SettingsButtonTex = IMG_LoadTexture(renderer, "assets/settings_button/settings6.png");
	SettingsButtonRect = CalculateRect(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f,false);


	ExitButtonTex = IMG_LoadTexture(renderer, "assets/exit/exit6.png");
	ExitButtonRect = CalculateRect(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f,false);
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
	if (NewGameButtonTex) {
		SDL_SetTextureScaleMode(NewGameButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, NewGameButtonTex, nullptr, &NewGameButtonRect);
	}
	if (PlayButtonTex) {
		SDL_SetTextureScaleMode(PlayButtonTex, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, PlayButtonTex, nullptr, &PlayButtonRect);
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
	MenuTitleRect = CalculateRect(MenuTitleTex, 0.55f, 0.25f, windowW, windowH, 0.05f, false);
	NewGameButtonRect = CalculateRect(NewGameButtonTex, 0.35f, 0.1f, windowW, windowH, 0.35f, false);
	PlayButtonRect = CalculateRect(PlayButtonTex, 0.35f, 0.1f, windowW, windowH, 0.5f, false);
	SettingsButtonRect = CalculateRect(SettingsButtonTex, 0.35f, 0.1f, windowW, windowH, 0.65f, false);
	ExitButtonRect = CalculateRect(ExitButtonTex, 0.35f, 0.1f, windowW, windowH, 0.8f, false);
}

void Menu::HandleMenuEvents(SDL_Event& event, bool& isRunning, GameState& currentState)
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_EVENT_QUIT) {
			isRunning = false;
		}
		if (event.type == SDL_EVENT_WINDOW_RESIZED) {
			int newW = event.window.data1;
			int newH = event.window.data2;
			UpdateLayout(newW, newH);
		}
	}
}



void Menu::CleanMenu()
{
	SDL_DestroyTexture(MenuBackgroundTex);
	SDL_DestroyTexture(MenuTitleTex);
	SDL_DestroyTexture(NewGameButtonTex);
	SDL_DestroyTexture(PlayButtonTex);
	SDL_DestroyTexture(SettingsButtonTex);
	SDL_DestroyTexture(ExitButtonTex);
}