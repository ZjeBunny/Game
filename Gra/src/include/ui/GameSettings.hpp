#pragma once
#include "../../include/Game.hpp"
#include "Slider.cpp"
#include <SDL3_ttf/SDL_ttf.h>
#include "GameMenu.hpp"
#include "Checkbox.cpp"
class SettingsSave;
class GSettings
{
	public:
		void LoadSettingsAssets(SDL_Renderer* renderer, int windowW, int windowH, SettingsSave* settingManager);
		void RenderSettings(SDL_Renderer* renderer);
		void UpdateLayout(int winW, int winH);
		void HandleSettingsEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer, SettingsSave* settingManager, SDL_Window* win);
		void CleanSettings();
		void HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos);
private:
	SettingsSave* sManager = nullptr;
	SDL_Texture* bg, *x, *save, *menu, *background = nullptr;
	SDL_FRect bgRect, xRect, saveRect, menuRect;
	SDL_FRect bgRect_base, xRect_base, saveRect_base, menuRect_base;
	TTF_Font* font = nullptr;
	bool changed = false;
	const char* title = "SETTINGS";
	const char* volume = "volume: ";
	const char* music = "music: ";
	const char* fullscreen = "fullscreen:";
	const char* showFps = "Show fps:";


	SDL_FRect titleR, volumeR, musicR, fpsR, fsR;
	SDL_Texture* titleTex, *volumeTex, *musicTex, * fullscreenTex, *fpsTex = nullptr;

	Slider volumeSlider;
	Slider musicSlider;
	SDL_Cursor* cursorPointer = nullptr;
	SDL_Cursor* cursorMove = nullptr;

	Checkbox fullCheckbox;
	Checkbox fpsCheckbox;
};