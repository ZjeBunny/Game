#pragma once

#include <SDL3/SDL.h>
#include <iostream>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#ifdef G_DEBUG
#define LOG(arg) std::cout <<arg<<"\n"
#else
#define LOG(arg)
#endif

class Game 
{
	public:
		Game();
		
		void init(const char* title, int width, int height, bool fullscreen, bool maximizeWindow);
		void handleEvents();
		void update();
		void render();
		void clean();

		bool running() { return isRunning; }

		unsigned long long previousStars = 0;
	private:
		bool isRunning;
		bool isFullscreen;
		SDL_Window *window;
		SDL_Renderer *renderer;
		Uint64 lastTime = 0;
		float deltaTime = 0.0f;
		TTF_Font *font = nullptr;
		SDL_FRect MainClicker;
		SDL_FRect PlayButtonRect;
};