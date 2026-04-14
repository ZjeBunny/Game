#pragma once
#include "../GameStateEnum.hpp"
#include "../Game.hpp"
class Main
{
public:
	void LoadMainAssets(SDL_Renderer* renderer, int windowW, int windowH);
	void RenderMain(SDL_Renderer* renderer);
	void UpdateLayout(int winW, int winH);
	void HandleMainEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer);
	void CleanMenu();
private:
	SDL_Texture *Background, *Clicker, *item1, *item2, *item3, *item4, *item5, *item_bg, *shop_icon,
		*shop_bg, *buy = nullptr;
	SDL_FRect ClickerRect, item1Rect, item2Rect, item3Rect, item4Rect, item5Rect, item_bgRect, shop_iconRect, buyRect, BackgroundRect ;
	SDL_Cursor* cursorPointer = nullptr;
	SDL_Cursor* cursorDefault = nullptr;
};