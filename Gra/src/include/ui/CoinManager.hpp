#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
struct SpawnPoint {
	float spx, spy;
	bool occupied;
};
struct ActiveCoin {
	SDL_FRect rect;
	int pointIndex;
	double value;
	SDL_Texture* texture;
};
class CoinManager
{
public:
	CoinManager();
	void SpawnCoin(int windowW, int windowH, SDL_Texture* tex1cent);
	void HandleCoinClick(float mouseX, float mouseY);
	void RenderCoins(SDL_Renderer* renderer, SDL_Texture* coinTex);
	void UpdatePosition(int windowW, int windowH);
	double getTotalMoney() const { return totalMoney; }
	bool isOverMoney(float mouseX, float mouseY);
	double substractMoney(double amount) { 
		if (amount > totalMoney) return -1.0;
		totalMoney -= amount; 
		return totalMoney;
	}
private:
	std::vector<SpawnPoint> SpawnPoints;
	std::vector<ActiveCoin> activeCoins;
	float coinScale = 0.03f;
	double totalMoney = 0.0;


	Uint64 lastSpawnTime = 0; 
	Uint64 spawnDelay = 6000;
	size_t maxCoins = 1;
};

