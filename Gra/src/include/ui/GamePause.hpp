#pragma once
#include "../Helpers.hpp"
class Pause
{
public:
	void LoadPauseAssets(SDL_Renderer* renderer, int windowW, int windowH);
	void Render(SDL_Renderer* renderer);
	void HandleInput(SDL_Event& event);
	

};