#include "src/Game.hpp"

Game *game = nullptr;   
int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Stock Market Simulator", 800, 600, false);

	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();

	}

	game->clean();
    return 0;
}