#pragma once
#include "../GameStateEnum.hpp"
#include "../Game.hpp"
class Menu
{
public:
	void LoadMenuAssets(SDL_Renderer* renderer, int windowW, int windowH);
	void RenderMenu(SDL_Renderer* renderer);
	void UpdateLayout(int winW, int winH);
	void HandleMenuEvents(SDL_Event& event, bool& isRunning, GameState& currentState);
	void CleanMenu();
	
	
private:
	SDL_Texture* MenuBackgroundTex = nullptr;
	SDL_FRect MenuBackgroundRect;

	SDL_Texture* MenuTitleTex = nullptr;
	SDL_FRect MenuTitleRect;

	SDL_Texture* NewGameButtonTex = nullptr;
	SDL_FRect NewGameButtonRect;

	SDL_Texture* PlayButtonTex = nullptr;
	SDL_FRect PlayButtonRect;

	SDL_Texture* SettingsButtonTex = nullptr;
	SDL_FRect SettingsButtonRect;


	SDL_Texture* ExitButtonTex = nullptr;
	SDL_FRect ExitButtonRect;
};