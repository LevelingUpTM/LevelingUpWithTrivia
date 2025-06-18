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

sqlite3 *SqliteDatabase::getDB() const
{
    return db;
}

bool SqliteDatabase::open()
{
    int result = sqlite3_open("TriviaDB.db", &db);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    // Enable foreign keys (if not active)
    sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, nullptr);

    char* errMsg = nullptr;

    // Create Users Table
    const char *createUsersTableQuery = "CREATE TABLE IF NOT EXISTS Users ("
                                        "UserID INTEGER PRIMARY KEY AUTOINCREMENT, "
                                        "Username TEXT NOT NULL UNIQUE, "
                                        "Password TEXT NOT NULL, "
                                        "Email TEXT NOT NULL);";

    result = sqlite3_exec(db, createUsersTableQuery, nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to create Users table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }


    // Create Statistics Teble
    const char *createStatisticsTableQuery = "CREATE TABLE IF NOT EXISTS statistics ("
                                             "UserID INTEGER PRIMARY KEY, "
                                             "TotalCorrectAnswers INTEGER DEFAULT 0, "
                                             "TotalAnswers INTEGER DEFAULT 0, "
                                             "TotalGames INTEGER DEFAULT 0, "
                                             "TotalTime REAL DEFAULT 0.0, "
                                             "FOREIGN KEY (UserID) REFERENCES Users(UserID) ON DELETE CASCADE);";


    result = sqlite3_exec(db, createStatisticsTableQuery, nullptr, nullptr, &errMsg);

    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to create statistics table: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }


    // Create Question Table
    const char *createQuestionsTableQuery = "CREATE TABLE IF NOT EXISTS questions ("
                                            "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                            "question TEXT, "
                                            "answer_1 TEXT, "
                                            "answer_2 TEXT, "
                                            "answer_3 TEXT, "
                                            "answer_4 TEXT, "
                                            "correct_answer INTEGER, "
                                            "difficulty TEXT, "
                                            "category TEXT);";


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

/*
for you to understand:
----------------------
if executing a statement that doesn't return results, using: sqlite3_exec

if executing a statement that does return results, using:
sqlite3_prepare_v2 - turn the query to bytes that sqlite can execute
sqlite3_step - executes the query now that its ready
sqlite3_finalize - closing and cleaning up the sql statement
*/

int SqliteDatabase::doesUserExist(const string username)
{
    const string query = "SELECT * FROM Users WHERE Username = '" + username + "';";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return 0;
    }

    int result = sqlite3_step(stmt);
    int userExists = 0;

    if (result == SQLITE_ROW)
    {
        userExists = 1;
    }
    else
    {
        userExists = 0;
    }

    sqlite3_finalize(stmt);
    return userExists;
}


int SqliteDatabase::doesPasswordMatch(const string username, const string password)
{
    const string query = "SELECT * FROM Users WHERE Username = '" + username + "' AND Password = '" + password + "';";
    sqlite3_stmt* stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return 0;
    }


    int result = sqlite3_step(stmt);
    int passMatch = 0;

    if (result == SQLITE_ROW)
    {
        passMatch = 1;
    }
    else
    {
        passMatch = 0;
    }

    sqlite3_finalize(stmt);

    return passMatch;
}


int SqliteDatabase::addNewUser(const string username, const string password, const string email)
{
    const string query = "INSERT INTO Users (Username, Password, Email) VALUES ('" +
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


std::list<Question> SqliteDatabase::getQuestions(int numOfQuestions)
{
    std::list<Question> questions;

    string query = "SELECT id, question, answer_1, answer_2, answer_3, answer_4, "
                        "correct_answer, difficulty, category "
                        "FROM questions "
                        "ORDER BY RANDOM() "
                        "LIMIT " +
                        std::to_string(numOfQuestions) + ";";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return questions;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        string questionText = (const char *)sqlite3_column_text(stmt, 1);
        string answer1 = (const char *)sqlite3_column_text(stmt, 2);
        string answer2 = (const char *)sqlite3_column_text(stmt, 3);
        string answer3 = (const char *)sqlite3_column_text(stmt, 4);
        string answer4 = (const char *)sqlite3_column_text(stmt, 5);
        unsigned int correctIndex = (unsigned int)sqlite3_column_int(stmt, 6);
        string difficulty = (const char *)sqlite3_column_text(stmt, 7);
        string category = (const char *)sqlite3_column_text(stmt, 8);

        vector<string> answers = {answer1, answer2, answer3, answer4};

        questions.emplace_back(id, questionText, answers, correctIndex, difficulty, category);
    }

    sqlite3_finalize(stmt);
    return questions;
}



int SqliteDatabase::getNumOfCorrectAnswers(const string &username)
{
    string query = "SELECT TotalCorrectAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = '" +
                        username + "';";

    sqlite3_stmt *stmt = nullptr;
    int correctAnswers = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            correctAnswers = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return correctAnswers;
}


int SqliteDatabase::getNumOfTotalAnswers(const string &username)
{
    string query = "SELECT TotalAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = '" +
                        username + "';";

    sqlite3_stmt *stmt = nullptr;
    int totalAnswers = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            totalAnswers = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return totalAnswers;
}


int SqliteDatabase::getNumOfPlayerGames(const string &username)
{
    string query = "SELECT TotalGames FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int totalGames = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            totalGames = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return totalGames;
}



float SqliteDatabase::getPlayerAverageAnswerTime(const string &username)
{
    string query = "SELECT TotalTime, TotalAnswers FROM statistics "
                   "JOIN Users ON Users.UserID = statistics.UserID "
                   "WHERE Username = '" +
                   username + "';";

    sqlite3_stmt *stmt = nullptr;
    float avgTime = 0.0f; // f makes it float and not double

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            float totalTime = (float)sqlite3_column_double(stmt, 0);
            int totalAnswers = sqlite3_column_int(stmt, 1);

            if (totalAnswers > 0)
            {
                avgTime = totalTime / totalAnswers;
            }
        }
    }

    sqlite3_finalize(stmt);
    return avgTime;
}



int SqliteDatabase::getPlayerScore(const string &username)
{
    string query = "SELECT TotalCorrectAnswers FROM statistics "
                   "JOIN Users ON Users.UserID = statistics.UserID "
                   "WHERE Username = '" +
                   username + "';";

    sqlite3_stmt *stmt = nullptr;
    int score = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            score = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return score;
}


vector<string> SqliteDatabase::getHighScores()
{
    vector<string> highScores;
    string query = "SELECT Username, TotalCorrectAnswers FROM statistics "
                   "JOIN Users ON Users.UserID = statistics.UserID "
                   "ORDER BY TotalCorrectAnswers DESC LIMIT 5;";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            string username = (const char *)sqlite3_column_text(stmt, 0);
            int score = sqlite3_column_int(stmt, 1);
            highScores.push_back(username + ": " + std::to_string(score) + " correct answers");
        }
    }

    sqlite3_finalize(stmt);
    return highScores;
}



void SqliteDatabase::submitStatistics(const string &userName, int correctAnswerCount, int wrongAnswerCount,
                                      int averageAnswerTime)
{
    sqlite3_stmt *stmt = nullptr;
    int userID = -1;
    string getUserIdQuery = "SELECT UserID FROM Users WHERE Username = '" + userName + "';";

    if (sqlite3_prepare_v2(db, getUserIdQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            userID = sqlite3_column_int(stmt, 0);
        }
        sqlite3_finalize(stmt);
    }

    if (userID == -1)
    {
        std::cerr << "Failed to find user ID for: " << userName << std::endl;
        return;
    }

    int totalAnswers = correctAnswerCount + wrongAnswerCount;
    string updateQuery = "UPDATE statistics SET "
                         "TotalCorrectAnswers = TotalCorrectAnswers + " + std::to_string(correctAnswerCount) + ", "
                         "TotalAnswers = TotalAnswers + " + std::to_string(totalAnswers) + ", "
                         "TotalGames = TotalGames + 1, "
                         "TotalTime = TotalTime + " + std::to_string(averageAnswerTime) + 
                         " WHERE UserID = " + std::to_string(userID) + ";";

    if (sqlite3_prepare_v2(db, updateQuery.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) != SQLITE_DONE)
        {
            std::cerr << "Failed to update statistics." << std::endl;
        }
        sqlite3_finalize(stmt);
    }

}