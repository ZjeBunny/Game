
#include "../include/GameSave.hpp"

using namespace std;
GameSave::GameSave()
{
    
}

void GameSave::callback(void* unused, int argc, char** argv, char** ColName)
{
    for (int i = 0; i < argc; i++)
    {
        cout << ColName[i] << ":" << argv[i] << endl;
    }
}

void GameSave::createDB(const char* s) 
{
    sqlite3* DB;
    int exit = 0;

    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);
}
void GameSave::createTableSaves(const char* s)
{
    sqlite3* DB;

    string sql("CREATE TABLE IF NOT EXISTS saves("
        "id     INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name   VARCHAR(255) NOT NULL,"
        "stars  INTEGER NOT NULL"
        ");");
    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) 
        {
            cerr << "Error creating table 1" << endl;
            sqlite3_free(messageError);
        }
        else
        {
               cout << "Table created" << endl;
               sqlite3_close(DB);
        }
    }
    catch (const exception & error)
    {
        cerr << error.what() << endl;
    }
}

void GameSave::createTableUpgrades(const char* s)
{
    sqlite3* DB;

    string sql("CREATE TABLE IF NOT EXISTS upgrades("
        "id     INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name   VARCHAR(255) NOT NULL,"
        "level  INTEGER NOT NULL DEFAULT 1,"
        "base_multiplier    INTEGER NOT NULL,"
        "saves_id   INTEGER NOT NULL,"
        "FOREIGN KEY(saves_id) REFERENCES saves(id)"
        ");");
    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error creating table 2" << endl;
            sqlite3_free(messageError);
        }
        else
        {
            cout << "Table created" << endl;
            sqlite3_close(DB);
        }
    }
    catch (const exception & error)
    {
        cerr << error.what() << endl;
    }
}

void GameSave::createSettingsTable(const char* s)
{
    sqlite3* DB;

    string sql("CREATE TABLE IF NOT EXISTS settings("
        "resolution     VARCHAR(50) NOT NULL DEFAULT '1600x900',"
        "fullscreen   BOOL NOT NULL DEFAULT true,"
        "volume     INTEGER NOT NULL DEFAULT 50,"
        "music      INTEGER NOT NULL DEFAULT 50,"
        "fps_counter    BOOL NOT NULL DEFAULT false"
        ");");
    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);

        char* messageError;
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK)
        {
            cerr << "Error creating table 3" << endl;
            sqlite3_free(messageError); 
        }
        else
        {
            cout << "Table created" << endl;
            sqlite3_close(DB);
        }
    }
    catch (const exception& error)
    {
        cerr << error.what() << endl;
    }
}

void GameSave::createSaveFile(const char* s,const char* name)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    string sql("INSERT INTO saves (name, stars) VALUES('" + string(name) + "', 0);");

    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
   
    if (exit != SQLITE_OK)
    {
        cerr << "Error insert" << endl;
        sqlite3_free(messageError);
    }
    else
    {
        cout << "Inserted data" << endl;
    }

}
void GameSave::updateSettings(const char* s, const char* res, bool fullscreen, int vol, int music, bool fps_counter)
{
    sqlite3* DB;
    char* messageError;

    int exit = sqlite3_open(s, &DB);

    std::string sql =
        "UPDATE settings "
        "SET resolution = ?, fullscreen = ?, volume = ?, music = ?, fps_counter = ?;";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Prepare failed" << endl;
        sqlite3_close(DB);

    }

    sqlite3_bind_text(stmt, 1, res, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, fullscreen ? 1 : 0);
    sqlite3_bind_int(stmt, 3, vol);
    sqlite3_bind_int(stmt, 4, music);
    sqlite3_bind_int(stmt, 5, fps_counter ? 1 : 0);


    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        std::cerr << "Execution failed" << endl;
        sqlite3_finalize(stmt);
        sqlite3_close(DB);

    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);
}

bool GameSave::load(const char* s, int saveId)
{
    sqlite3* DB;
    sqlite3_stmt* stmt;

    upgrades.clear();

    int exit = sqlite3_open(s, &DB);
    if (exit != SQLITE_OK)
    {
        std::cerr << "Cannot open DB" << endl;
        return false;
    }

    sqlite3_exec(DB, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    std::string sql =
        "SELECT saves.name, saves.stars, upgrades.name, upgrades.level "
        "FROM saves "
        "LEFT JOIN upgrades ON saves.id = upgrades.saves_id "
        "WHERE saves.id = ?;";

    if (sqlite3_prepare_v2(DB, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK)
    {
        std::cerr << "Prepare failed" << endl;
        sqlite3_close(DB);
        return false;
    }


    sqlite3_bind_int(stmt, 1, saveId);

    bool initialized = false;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {

        const unsigned char* sNameText = sqlite3_column_text(stmt, 0);

        if (!initialized)
        {
            name = sNameText ? reinterpret_cast<const char*>(sNameText) : "";
            stars = sqlite3_column_int(stmt, 1);
            initialized = true;
        }

        const unsigned char* upNameText = sqlite3_column_text(stmt, 2);

        if (upNameText)
        {
            std::string upName = reinterpret_cast<const char*>(upNameText);
            int upLevel = sqlite3_column_int(stmt, 3);

            upgrades.push_back({ upName, upLevel });
        }
    }

    sqlite3_finalize(stmt);
    sqlite3_close(DB);

    if (!initialized)
    {
        std::cerr << "Save ID not found" << endl;
        return false;
    }

    return true;
}
