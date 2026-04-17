#include "./include/Game.hpp"
#include <SDL3/SDL_main.h>
#include "./include/SettingsManager.hpp"

std::unique_ptr<Game> game = std::make_unique<Game>();
std::unique_ptr<SettingsSave> settings = std::make_unique<SettingsSave>();
int main(int argc, char* argv[])
{
	settings->CreateSettingsSave("src/save/GameSettings.db");
	settings->LoadSettings();
	Config gameConf = settings->GetConfig();

	int width, height;
	if (sscanf_s(gameConf.resolution.c_str(), "%dx%d", &width, &height) != 2) {
		width = 1280;
		height = 960;
	}
	game->init("Yahul Clicker", width, height, gameConf.isFullscreen, gameConf.showFps, settings.get());
	
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}
	
	game->clean();
	return SDL_APP_SUCCESS;
}