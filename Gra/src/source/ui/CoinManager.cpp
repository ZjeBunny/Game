#include "../../include/ui/CoinManager.hpp"
CoinManager::CoinManager() {
    for (float x = 0.22f; x <= 0.8f; x += 0.0005f) {
        for (float y = 0.24f; y <= 0.82f; y += 0.0005f) {
            SpawnPoints.push_back({ x, y, false });
        }
    }
}

void CoinManager::SpawnCoin(int windowW, int windowH, SDL_Texture* tex1cent) {
    Uint64 currentTime = SDL_GetTicks();

    if (activeCoins.size() >= maxCoins) {
        lastSpawnTime = currentTime;
        return;
    }

    if (currentTime - lastSpawnTime >= spawnDelay) {
        std::vector<int> freeIndices;
        for (int i = 0; i < (int)SpawnPoints.size(); ++i) {
            if (!SpawnPoints[i].occupied) {
                freeIndices.push_back(i);
            }
        }

        if (freeIndices.empty()) {
            lastSpawnTime = currentTime;
            return;
        }

        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distIdx(0, (int)freeIndices.size() - 1);
        int chosenIdx = freeIndices[distIdx(gen)];

        std::uniform_int_distribution<> distVal(1, 100);
        int roll = distVal(gen);

        double val = 0.0;
        SDL_Texture* selectedTex = nullptr;

        if (roll <= 100) {
            val = 0.01;
            selectedTex = tex1cent;
        }

        float size = windowW * coinScale;
        float xPos = (SpawnPoints[chosenIdx].spx * windowW) - (size / 2.0f);
        float yPos = (SpawnPoints[chosenIdx].spy * windowH) - (size / 2.0f);

        SpawnPoints[chosenIdx].occupied = true;
        activeCoins.push_back({ {xPos, yPos, size, size}, chosenIdx, val, selectedTex });

        lastSpawnTime = currentTime;
    }
}

void CoinManager::HandleCoinClick(float mouseX, float mouseY) {
    
    for (auto it = activeCoins.begin(); it != activeCoins.end(); ) {
        SDL_FPoint mousePt = { mouseX, mouseY };
        if (SDL_PointInRectFloat(&mousePt, &it->rect)) {
            totalMoney += it->value;
            SpawnPoints[it->pointIndex].occupied = false;
            it = activeCoins.erase(it);
        }
        else {
            ++it;
        }
    }
}

bool CoinManager::isOverMoney(float mouseX, float mouseY) {
    for (const auto& coin : activeCoins) {
        SDL_FPoint mousePt{ mouseX, mouseY };
        if (SDL_PointInRectFloat(&mousePt, &coin.rect)) {
            return true;
        }
    }
    return false;
}

void CoinManager::UpdatePosition(int windowW, int windowH) {
    float size = windowW * coinScale;
    for (auto& coin : activeCoins) {
        coin.rect.w = size;
        coin.rect.h = size;
        coin.rect.x = (SpawnPoints[coin.pointIndex].spx * windowW) - (size / 2.0f);
        coin.rect.y = (SpawnPoints[coin.pointIndex].spy * windowH) - (size / 2.0f);
    }
}
void CoinManager::RenderCoins(SDL_Renderer* renderer, SDL_Texture* coinTex) {
    for (const auto& coin : activeCoins) {
        SDL_RenderTexture(renderer, coinTex, NULL, &coin.rect);
    }
}

double getRandomCoinValue() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);
    int roll = dist(gen);

    if (roll <= 100) return 0.01;
   
}