#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>


class GameSave
{
public:
    bool load(const char* s, int saveId);
    void print() const;

private:
    std::string name;
    int stars = 0;

    std::vector<std::pair<std::string, int>> upgrades;
};

int createDB(const char* s);
int createTableSaves(const char* s);
int createTableUpgrades(const char* s);
int createSettingsTable(const char* s);
int createSaveFile(const char* s, char* name);
int updateSettings(const char* s, const char* res, bool fullscreen, int vol, int music, bool fps_counter);

#endif#