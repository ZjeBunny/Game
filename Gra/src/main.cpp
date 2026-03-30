#include "./include/Game.hpp"
#include <SDL3/SDL_main.h>
Game *game = nullptr;   
int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Yahuk incremental clicker", 1280, 960, false, false);
	
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}

	game->clean();
    return 0;
}