#include "./include/Game.hpp"
#include <SDL3/SDL_main.h>
std::unique_ptr<Game> game = std::make_unique<Game>();
int main(int argc, char* argv[])
{

	game->init("Yahul incremental clicker", 1200, 900, false, true);
	
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	game->clean();
	return SDL_APP_SUCCESS;
}