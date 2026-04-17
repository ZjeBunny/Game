#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>
#include <map>
struct Upgrade {
    int id;
    std::string name;
    int level;
    int maxLevel;      
    double base_multiplier;
    std::string texture; 
};
class GameSave {
public:
    ~GameSave() { if (DB) sqlite3_close(DB); }

    void CreateGameSave(const char* path);
    void LoadGameSave(int saveId);
    void SaveGame(const Upgrade& up);
    void AutoSaveAll(double currentMoney, const std::map<std::string, Upgrade>& currentUpgrades);
    std::map<std::string, Upgrade>& GetUpgrades() { return upgrades; }
    double GetMoney() const { return money; };

private:
    sqlite3* DB = nullptr;
    int currentSaveId = -1;

    double money = 0.0;
    std::string saveName;

    std::map<std::string, Upgrade> upgrades;
};