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


sqlite3 *SqliteDatabase::getDB() const
{
    return db;
}


std::list<Question> SqliteDatabase::getQuestions(int numOfQuestions)
{
    std::list<Question> questions;

    std::string query = R"(
        SELECT id, question, answer_1, answer_2, answer_3, answer_4,
               correct_answer, difficulty, category
        FROM questions
        ORDER BY RANDOM()
        LIMIT ?;
    )";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
        return questions;

    sqlite3_bind_int(stmt, 1, numOfQuestions);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        std::string questionText = (const char *)sqlite3_column_text(stmt, 1);
        std::string answer1 = (const char *)sqlite3_column_text(stmt, 2);
        std::string answer2 = (const char *)sqlite3_column_text(stmt, 3);
        std::string answer3 = (const char *)sqlite3_column_text(stmt, 4);
        std::string answer4 = (const char *)sqlite3_column_text(stmt, 5);
        unsigned int correctIndex = (unsigned int)sqlite3_column_int(stmt, 6);
        std::string difficulty = (const char *)sqlite3_column_text(stmt, 7);
        std::string category = (const char *)sqlite3_column_text(stmt, 8);

        std::vector<std::string> answers = {answer1, answer2, answer3, answer4};

        questions.emplace_back(id, questionText, answers, correctIndex, difficulty, category);
    }

    sqlite3_finalize(stmt);
    return questions;
}

int SqliteDatabase::getNumOfCorrectAnswers(const std::string &username)
{
    std::string query = "SELECT TotalCorrectAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int correctAnswers = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            correctAnswers = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return correctAnswers;
}

int SqliteDatabase::getNumOfTotalAnswers(const std::string &username)
{
    std::string query = "SELECT TotalAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int totalAnswers = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            totalAnswers = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return totalAnswers;
}

int SqliteDatabase::getNumOfPlayerGames(const std::string &username)
{
    std::string query = "SELECT TotalGames FROM statistics "
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





float SqliteDatabase::getPlayerAverageAnswerTime(const std::string &username)
{
    std::string query = "SELECT TotalTime, TotalAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    float avgTime = 0.0f;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

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

int SqliteDatabase::getPlayerScore(const std::string &username)
{
    const std::string query = R"(
        SELECT TotalCorrectAnswers
        FROM statistics
        JOIN Users ON Users.UserID = statistics.UserID
        WHERE Username = ?;
    )";

    sqlite3_stmt *stmt = nullptr;
    int score = 0;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            score = sqlite3_column_int(stmt, 0);
        }
    }

    sqlite3_finalize(stmt);
    return score;
}



std::vector<std::string> SqliteDatabase::getHighScores()
{
    std::vector<std::string> highScores;
    const std::string query = R"(
        SELECT Username, TotalCorrectAnswers
        FROM statistics
        JOIN Users ON Users.UserID = statistics.UserID
        ORDER BY TotalCorrectAnswers DESC
        LIMIT 5;
    )";

    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::string username = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
            int score = sqlite3_column_int(stmt, 1);
            highScores.push_back(username + ": " + std::to_string(score) + " correct answers");
        }
    }

    sqlite3_finalize(stmt);
    return highScores;
}

void SqliteDatabase::submitStatistics(const std::string &userName, int correctAnswerCount, int wrongAnswerCount,
                                      int avarageAnswerTime)
{
    char *errMsg = nullptr;

    std::string getUserIdQuery = "SELECT UserID FROM Users WHERE Username = '" + userName + "';";
    int userID = -1;

    sqlite3_exec(
        db, getUserIdQuery.c_str(),
        [](void *data, int argc, char **argv, char **azColName) -> int {
            int *id = static_cast<int *>(data);
            if (argc > 0 && argv[0])
                *id = std::stoi(argv[0]);
            return 0;
        },
        &userID, &errMsg);

    if (userID == -1)
    {
        std::cerr << "Failed to find user ID for: " << userName << std::endl;
        if (errMsg)
            sqlite3_free(errMsg);
        return;
    }

    int totalAnswersToAdd = correctAnswerCount + wrongAnswerCount;

    std::string updateStatisticsQuery = "UPDATE statistics SET "
                                        "TotalCorrectAnswers = TotalCorrectAnswers + " +
                                        std::to_string(correctAnswerCount) +
                                        ", "
                                        "TotalAnswers = TotalAnswers + " +
                                        std::to_string(totalAnswersToAdd) +
                                        ", "
                                        "TotalGames = TotalGames + 1, "
                                        "TotalTime = TotalTime + " +
                                        std::to_string(avarageAnswerTime) +
                                        " WHERE UserID = " + std::to_string(userID) + ";";

    int result = sqlite3_exec(db, updateStatisticsQuery.c_str(), nullptr, nullptr, &errMsg);
    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to update statistics: " << (errMsg ? errMsg : "Unknown error") << std::endl;
        if (errMsg)
            sqlite3_free(errMsg);
    }
}
