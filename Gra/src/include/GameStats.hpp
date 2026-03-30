#pragma once
class GameStats
{
public:
	GameStats();
	~GameStats();
	void GameLoadStats();
	void GameIcremeantStars();
	unsigned long long GetStars() { return stars; };
private:
	unsigned long long stars;
};

