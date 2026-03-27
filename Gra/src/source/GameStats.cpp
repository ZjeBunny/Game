#include "../include/GameStats.hpp"
double multiplier = 1.0;

GameStats::GameStats() : stars(100000)
{
}

GameStats::~GameStats()
{
}

void GameStats::GameLoadStats() {

}

void GameStats::GameIcremeantStars() {
	int starsFromClick = 1 * multiplier;
	stars += starsFromClick;
}