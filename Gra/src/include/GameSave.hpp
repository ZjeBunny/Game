#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <iostream>
#include "../lib/sqlite3.h"

class GameSave
{
public:
	GameSave();
    bool load(const char* s, int saveId);
    void print() const;
	void callback(void* unused, int argc, char** argv, char** ColName);
    void createDB(const char* s);
    void createTableSaves(const char* s);
    void createTableUpgrades(const char* s);
    void createSettingsTable(const char* s);
    void createSaveFile(const char* s, char* name);
    void updateSettings(const char* s, const char* res, bool fullscreen, int vol, int music, bool fps_counter);

private:
    std::string name;
    int stars = 0;

    std::vector<std::pair<std::string, int>> upgrades;
};



#endif