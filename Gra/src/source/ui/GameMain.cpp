#include "../../include/ui/GameMain.hpp"
#include "../../include/Helpers.cpp"

void Main::LoadMainAssets(SDL_Renderer* renderer, int windowW, int windowH)
{
	cursorPointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
	cursorDefault = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);

	Background;
	BackgroundRect;

	Clicker = IMG_LoadTexture(renderer, "assets/main_clicker/main_clicker.png");
	ClickerRect = CalculateRect(Clicker, 0.3f, 0.3f, windowH, windowH, 0.5f, 0.2f, true);
}

void Main::RenderMain(SDL_Renderer* renderer)
{
	if(Clicker) {
		SDL_SetTextureScaleMode(Clicker, SDL_SCALEMODE_PIXELART);
		SDL_RenderTexture(renderer, Clicker, nullptr, &ClickerRect);
	}
}

void Main::UpdateLayout(int winW, int winH)
{
}

void Main::HandleMainEvents(SDL_Event& event, bool& isRunning, GameState& currentState, SDL_Renderer* renderer)
{
}

void Main::CleanMenu()
{
}
