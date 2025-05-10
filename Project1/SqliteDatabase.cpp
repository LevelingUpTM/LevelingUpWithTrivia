#include "SqliteDatabase.h"
#include <iostream>

SqliteDatabase::SqliteDatabase()
    : db(nullptr)
{
}

SqliteDatabase::~SqliteDatabase()
{
    SqliteDatabase::close();
}

bool SqliteDatabase::open()
{
    int result = sqlite3_open("TriviaDB.db", &db);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Enable foreign keys
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    const char* createUsersTableQuery =
        "CREATE TABLE IF NOT EXISTS Users ("
        "UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "Username TEXT NOT NULL UNIQUE, "
        "Password TEXT NOT NULL, "
        "Email TEXT NOT NULL);";

    const char* createStatisticsTableQuery =
        "CREATE TABLE IF NOT EXISTS statistics ("
        "UserID INTEGER PRIMARY KEY, "
        "TotalCorrectAnswers INTEGER DEFAULT 0, "
        "TotalAnswers INTEGER DEFAULT 0, "
        "TotalGames INTEGER DEFAULT 0, "
        "TotalTime REAL DEFAULT 0.0, "
        "FOREIGN KEY (UserID) REFERENCES Users(UserID) ON DELETE CASCADE);";

    const char* createQuestionsTableQuery =
        "CREATE TABLE IF NOT EXISTS questions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "question TEXT, "
        "answer_1 TEXT, "
        "answer_2 TEXT, "
        "answer_3 TEXT, "
        "answer_4 TEXT, "
        "correct_answer INTEGER, "
        "difficulty TEXT, "
        "category TEXT);";

    char* errMsg = nullptr;

    result = sqlite3_exec(db, createUsersTableQuery, nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to create Users table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    result = sqlite3_exec(db, createStatisticsTableQuery, nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to create statistics table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    result = sqlite3_exec(db, createQuestionsTableQuery, nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to create questions table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }

    return true;
}

bool SqliteDatabase::close()
{
    if (db)
    {
        const int result = sqlite3_close(db);
        db = nullptr;
        return result == SQLITE_OK;
    }
    return false;
}

int SqliteDatabase::doesUserExist(const std::string username)
{
    const std::string query = "SELECT * FROM Users WHERE Username = '" + username + "';";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return 0;
    }

    const int result = (sqlite3_step(stmt) == SQLITE_ROW) ? 1 : 0;
    sqlite3_finalize(stmt);
    return result;
}

int SqliteDatabase::doesPasswordMatch(const std::string username, const std::string password)
{
    const std::string query = "SELECT * FROM Users WHERE Username = '" + username + "' AND Password = '" + password + "';";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return 0;
    }

    const int result = (sqlite3_step(stmt) == SQLITE_ROW) ? 1 : 0;
    sqlite3_finalize(stmt);
    return result;
}

int SqliteDatabase::addNewUser(const std::string username, const std::string password, const std::string email)
{
    const std::string query = "INSERT INTO Users (Username, Password, Email) VALUES ('" +
        username + "', '" + password + "', '" + email + "');";
    char* errMsg = nullptr;

    const int result = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        if (errMsg)
        {
            std::cerr << "Failed to add new user: " << errMsg << std::endl;
            sqlite3_free(errMsg);
        }
        else
        {
            std::cerr << "Failed to add new user: Unknown error" << std::endl;
        }
        return 0;
    }

    return 1;
}

bool SqliteDatabase::addQuestions()
{
    return false;
}
