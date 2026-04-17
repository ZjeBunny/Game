#pragma once 
#include <sqlite3.h>
#include <string>
#include <iostream>
#include "Game.hpp"
struct Config {
    std::string resolution = "1280x960";
    int soundVolume = 50;
    int musicVolume = 50;
    bool isFullscreen = true;
    bool showFps = false;
};

class SettingsSave {
public:
    void CreateSettingsSave(const char* path);
    void LoadSettings();
    void SaveSettingsToDB();
    const Config& GetConfig() const { return conf; }
    void SetConfig(const Config& newConf) {
        conf = newConf;
    }
    void CloseSettingsSave() {
        if (DB) {
            sqlite3_close(DB);
            DB = nullptr;
        }
    }
private:
    sqlite3* DB = nullptr;
    Config conf;
};
extern std::unique_ptr<SettingsSave> settings;
