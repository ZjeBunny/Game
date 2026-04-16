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
	void HoverEffect(SDL_FRect* currentRect, const SDL_FRect& baseRect, const SDL_FPoint& mousePos);
	bool NewGamePrompt(SDL_Renderer* renderer, int windowW, int windowH, TTF_Font* font, SDL_Event& event);
private:
	SDL_Texture* MenuBackgroundTex = nullptr;
	SDL_FRect MenuBackgroundRect;

	SDL_Texture* MenuTitleTex = nullptr;
	SDL_FRect MenuTitleRect;

	SDL_Texture* NewGameButtonTex = nullptr;
	SDL_FRect NewGameButtonRect, NewGameButtonRect_Base;

	SDL_Texture* ContinueButtonTex = nullptr;
	SDL_FRect ContinueButtonRect, ContinueButtonRect_Base;

	SDL_Texture* SettingsButtonTex = nullptr;
	SDL_FRect SettingsButtonRect, SettingsButtonRect_Base;


	SDL_Texture* ExitButtonTex = nullptr;
	SDL_FRect ExitButtonRect, ExitButtonRect_Base;

	SDL_Cursor* cursorPointer = nullptr;
	SDL_Cursor* cursorDefault = nullptr;

	SDL_Texture* PromptBackgroundTex = nullptr;
	SDL_FRect PromptBackgroundRect;

	const char* newGameTextQuestion = "Do you want to start New Game?";
	const char* newGameTextWarning = "Your current progress will be lost";
	const char* newGameTextYes = "Yes";
	const char* newGameTextNo = "No";
	TTF_Font* font = nullptr;
	SDL_FRect newGameTextQuestionRect, newGameTextWarningRect, newGameTextYesRect, newGameTextNoRect;
	SDL_FRect newGameTextYesRect_Base, newGameTextNoRect_Base;
	SDL_Texture* newGameTextQuestionTex, * newGameTextWarningTex, * newGameTextYesTex, *newGameTextNoTex = nullptr;
};