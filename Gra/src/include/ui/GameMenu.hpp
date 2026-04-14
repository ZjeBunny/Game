#pragma once
#include "../GameStateEnum.hpp"
#include "../Game.hpp"
class Menu
{
public:
	void LoadMenuAssets(SDL_Renderer* renderer, int windowW, int windowH);
	void RenderMenu(SDL_Renderer* renderer);
	void UpdateLayout(int winW, int winH);
	void HandleMenuEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer);
	void CleanMenu();
	inline void RunAnimation(SDL_Renderer* renderer, SDL_Texture*& TexName, const std::string& TexPath, int AmmountOfFrames, int delayMS);
	
private:
	SDL_Texture* MenuBackgroundTex = nullptr;
	SDL_FRect MenuBackgroundRect;

	SDL_Texture* MenuTitleTex = nullptr;
	SDL_FRect MenuTitleRect;

	SDL_Texture* NewGameButtonTex = nullptr;
	SDL_FRect NewGameButtonRect;

	SDL_Texture* ContinueButtonTex = nullptr;
	SDL_FRect ContinueButtonRect;

	SDL_Texture* SettingsButtonTex = nullptr;
	SDL_FRect SettingsButtonRect;


	SDL_Texture* ExitButtonTex = nullptr;
	SDL_FRect ExitButtonRect;

	SDL_Cursor* cursorPointer = nullptr;
	SDL_Cursor* cursorDefault = nullptr;
};