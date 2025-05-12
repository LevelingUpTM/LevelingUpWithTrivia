#include "StatisticsManager.h"
#include "SqliteDatabase.h"
#include <iostream>
#include <sstream>
#include "sqlite3.h"


StatisticsManager::StatisticsManager(IDatabase *db) : m_database(db)
{
}

std::vector<std::string> StatisticsManager::getHighScore()
{
    // Not implemented yet – placeholder
    return {"High score feature not implemented."};
}

std::vector<std::string> StatisticsManager::getUserStatistics(const std::string &username)
{
    std::vector<std::string> stats;

    int correctAnswers = getNumOfCorrectAnswers(username);
    int totalAnswers = getNumOfTotalAnswers(username);
    int totalGames = getNumOfPlayerGames(username);
    float avgAnswerTime = getPlayerAverageAnswerTime(username);

    stats.push_back("Correct Answers: " + std::to_string(correctAnswers));
    stats.push_back("Total Answers: " + std::to_string(totalAnswers));
    stats.push_back("Total Games: " + std::to_string(totalGames));
    stats.push_back("Average Answer Time: " + std::to_string(avgAnswerTime));

    return stats;
}

int StatisticsManager::getNumOfCorrectAnswers(const std::string &username)
{
    std::string query = "SELECT TotalCorrectAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int correctAnswers = 0;

    if (sqlite3_prepare_v2(m_database->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
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

int StatisticsManager::getNumOfTotalAnswers(const std::string &username)
{
    std::string query = "SELECT TotalAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int totalAnswers = 0;

    if (sqlite3_prepare_v2(m_database->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
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

int StatisticsManager::getNumOfPlayerGames(const std::string &username)
{
    std::string query = "SELECT TotalGames FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    int totalGames = 0;

    if (sqlite3_prepare_v2(m_database->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
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

float StatisticsManager::getPlayerAverageAnswerTime(const std::string &username)
{
    std::string query = "SELECT TotalTime, TotalAnswers FROM statistics "
                        "JOIN Users ON Users.UserID = statistics.UserID "
                        "WHERE Username = ?;";
    sqlite3_stmt *stmt;
    float avgTime = 0.0f;

    if (sqlite3_prepare_v2(m_database->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            float totalTime = static_cast<float>(sqlite3_column_double(stmt, 0));
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
