
#include "../include/GameSave.hpp"
#include <iostream>
void GameSave::CreateGameSave(const char* path) {
    if (sqlite3_open(path, &DB) != SQLITE_OK) {
        return;
    }

    const char* sql =
        "CREATE TABLE IF NOT EXISTS saves("
        "id     INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name   TEXT NOT NULL,"
        "money  DOUBLE NOT NULL DEFAULT 0.0"
        ");"
        "CREATE TABLE IF NOT EXISTS upgrades("
        "id     INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name   TEXT NOT NULL,"
        "level  INTEGER NOT NULL DEFAULT 1,"
        "max_level INTEGER NOT NULL DEFAULT 10,"
        "base_multiplier DOUBLE NOT NULL,"
        "texture VARCHAR(255),"                  
        "saves_id INTEGER NOT NULL,"
        "FOREIGN KEY(saves_id) REFERENCES saves(id),"
        "UNIQUE(name, saves_id)"
        ");";

    char* msgErr = nullptr;
    if (sqlite3_exec(DB, sql, nullptr, 0, &msgErr) != SQLITE_OK) {
        sqlite3_free(msgErr);
    }
}
void GameSave::LoadGameSave(int saveId)
{
    this->currentSaveId = saveId;
    this->upgrades.clear();

    const char* sqlSave = "SELECT name, money FROM saves WHERE id = ?;";
    sqlite3_stmt* stmtSave;
    bool found = false;

    if (sqlite3_prepare_v2(DB, sqlSave, -1, &stmtSave, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmtSave, 1, saveId);
        if (sqlite3_step(stmtSave) == SQLITE_ROW) {
            this->saveName = reinterpret_cast<const char*>(sqlite3_column_text(stmtSave, 0));
            this->money = sqlite3_column_double(stmtSave, 1);
            found = true;
        }
        sqlite3_finalize(stmtSave);
    }

    if (!found) {
        const char* sqlInsert = "INSERT INTO saves (id, name, money) VALUES (?, 'Player', 0.0);";
        sqlite3_stmt* stmtIns;
        if (sqlite3_prepare_v2(DB, sqlInsert, -1, &stmtIns, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmtIns, 1, saveId);
            sqlite3_step(stmtIns);
            sqlite3_finalize(stmtIns);
        }
        this->money = 0.0;
        this->saveName = "Player";
    }
    
    const char* sqlUpgrades = "SELECT id, name, level, max_level, base_multiplier, texture FROM upgrades WHERE saves_id = ?;";
    sqlite3_stmt* stmtUp;

    if (sqlite3_prepare_v2(DB, sqlUpgrades, -1, &stmtUp, nullptr) == SQLITE_OK) {
        sqlite3_bind_int(stmtUp, 1, saveId);
        while (sqlite3_step(stmtUp) == SQLITE_ROW) {
            Upgrade up;
            up.id = sqlite3_column_int(stmtUp, 0);
            up.name = reinterpret_cast<const char*>(sqlite3_column_text(stmtUp, 1));
            up.level = sqlite3_column_int(stmtUp, 2);
            up.maxLevel = sqlite3_column_int(stmtUp, 3);
            up.base_multiplier = sqlite3_column_int(stmtUp, 4);
            const char* tex = reinterpret_cast<const char*>(sqlite3_column_text(stmtUp, 5));
            up.texture = tex ? tex : "";

            this->upgrades[up.name] = up;
        }
        sqlite3_finalize(stmtUp);
    }
}
void GameSave::SaveGame(const Upgrade& up) {
    if (!DB || currentSaveId == -1) return;
    const char* sqlStats = "UPDATE saves SET money = ?, name = ? WHERE id = ?;";
    sqlite3_stmt* stmtStats;
    if (sqlite3_prepare_v2(DB, sqlStats, -1, &stmtStats, nullptr) == SQLITE_OK) {
        sqlite3_bind_double(stmtStats, 1, this->money);
        sqlite3_bind_text(stmtStats, 2, this->saveName.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtStats, 3, this->currentSaveId);

        sqlite3_step(stmtStats);
        sqlite3_finalize(stmtStats);
    }

    const char* sqlUp =
        "INSERT OR REPLACE INTO upgrades (name, level, max_level, base_multiplier, texture, saves_id) "
        "VALUES (?, ?, ?, ?, ?, ?);";

    sqlite3_stmt* stmtUp;
    if (sqlite3_prepare_v2(DB, sqlUp, -1, &stmtUp, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmtUp, 1, up.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtUp, 2, up.level);
        sqlite3_bind_int(stmtUp, 3, up.maxLevel);
        sqlite3_bind_int(stmtUp, 4, up.base_multiplier);
        sqlite3_bind_text(stmtUp, 5, up.texture.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int(stmtUp, 6, currentSaveId);

        if (sqlite3_step(stmtUp) == SQLITE_DONE) {
            this->upgrades[up.name] = up;
        }
        sqlite3_finalize(stmtUp);
    }
}

void GameSave::AutoSaveAll(double currentMoney, const std::map<std::string, Upgrade>& currentUpgrades) {
    if (!DB || currentSaveId == -1) return;
    sqlite3_exec(DB, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr);

    const char* sqlMoney = "UPDATE saves SET money = ? WHERE id = ?;";
    sqlite3_stmt* stmtM;
    if (sqlite3_prepare_v2(DB, sqlMoney, -1, &stmtM, nullptr) == SQLITE_OK) {
        sqlite3_bind_double(stmtM, 1, currentMoney);
        sqlite3_bind_int(stmtM, 2, currentSaveId);
        sqlite3_step(stmtM);
        sqlite3_finalize(stmtM);
    }

    const char* sqlUp = "UPDATE upgrades SET level = ? WHERE name = ? AND saves_id = ?;";
    sqlite3_stmt* stmtUp;
    if (sqlite3_prepare_v2(DB, sqlUp, -1, &stmtUp, nullptr) == SQLITE_OK) {
        for (auto const& [name, up] : currentUpgrades) {
            sqlite3_bind_int(stmtUp, 1, up.level);
            sqlite3_bind_text(stmtUp, 2, name.c_str(), -1, SQLITE_TRANSIENT);
            sqlite3_bind_int(stmtUp, 3, currentSaveId);
            sqlite3_step(stmtUp);
            sqlite3_reset(stmtUp);
        }
        sqlite3_finalize(stmtUp);
    }
    sqlite3_exec(DB, "COMMIT;", nullptr, nullptr, nullptr);
}