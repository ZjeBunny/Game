#include "../include/GameStats.hpp"
float multiplier = 5.0f;

GameStats::GameStats() : stars(0)
{
}

GameStats::~GameStats()
{
}

void GameStats::GameLoadStats() {

}

void GameStats::GameIcremeantStars() {
	float starsFromClick = 1.0f * multiplier;
	stars += starsFromClick;
}