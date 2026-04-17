
#include"../include/SettingsManager.hpp"

void SettingsSave::CreateSettingsSave(const char* path) {
    int returnCode = sqlite3_open(path, &DB);
    if (returnCode!= SQLITE_OK) {
        LOG("Failed to open base: " << sqlite3_errmsg(DB));
        DB = nullptr;
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS settings("
        "id INTEGER PRIMARY KEY CHECK (id = 1),"
        "resolution TEXT, volume INTEGER, music INTEGER, "
        "fullscreen INTEGER, showFps INTEGER);";

    char* msgErr = nullptr;
    if (sqlite3_exec(DB, sql, nullptr, nullptr, &msgErr) != SQLITE_OK) {
        LOG("SQL Error (CreateTable): " << msgErr);
        sqlite3_free(msgErr);
    }
}

void SettingsSave::LoadSettings() {
    if (!DB) return;

    const char* sql = "SELECT resolution, volume, music, fullscreen, showFps FROM settings WHERE id = 1;";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        LOG("error prepare: " << sqlite3_errmsg(DB));
        return;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {

        const unsigned char* text = sqlite3_column_text(stmt, 0);
        if (text)
            conf.resolution = reinterpret_cast<const char*>(text);

        conf.soundVolume = sqlite3_column_int(stmt, 1);
        conf.musicVolume = sqlite3_column_int(stmt, 2);
        conf.isFullscreen = sqlite3_column_int(stmt, 3) != 0;
        conf.showFps = sqlite3_column_int(stmt, 4) != 0;

        LOG("loaded: " << conf.resolution);
    }
    else {
        LOG("No settings, using default values");
        SaveSettingsToDB();
    }

    sqlite3_finalize(stmt);
}

void SettingsSave::SaveSettingsToDB() {
    if (!DB) return;

    const char* sql =
        "INSERT OR REPLACE INTO settings "
        "(id, resolution, volume, music, fullscreen, showFps) "
        "VALUES (1, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(DB, sql, -1, &stmt, nullptr) != SQLITE_OK) {
        LOG("Save fail: " << sqlite3_errmsg(DB));
        return;
    }

    sqlite3_bind_text(stmt, 1, conf.resolution.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, conf.soundVolume);
    sqlite3_bind_int(stmt, 3, conf.musicVolume);
    sqlite3_bind_int(stmt, 4, conf.isFullscreen ? 1 : 0);
    sqlite3_bind_int(stmt, 5, conf.showFps ? 1 : 0);

    if (sqlite3_step(stmt) != SQLITE_DONE) {
        LOG("Failed to save settings: " << sqlite3_errmsg(DB));
    }

    sqlite3_finalize(stmt);
}
