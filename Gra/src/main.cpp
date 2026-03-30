#include "./include/Game.hpp"
#include <SDL3/SDL_main.h>
std::unique_ptr<Game> game = std::make_unique<Game>();
int main(int argc, char* argv[])
{
	game->init("Yahuk incremental clicker", 1280, 960, false, false);
	
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}
	
	game->clean();
	game.reset();
    return 0;
}