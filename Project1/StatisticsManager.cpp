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
    std::vector<std::string> highScores; // will be vector of string like "Name: # correct answers"
    std::string query = R"(
        SELECT Username, TotalCorrectAnswers
        FROM statistics
        JOIN Users ON Users.UserID = statistics.UserID
        ORDER BY TotalCorrectAnswers DESC
        LIMIT 5;
    )";

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(m_database->getDB(), query.c_str(), -1, &stmt, nullptr) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            std::string username = (const char *)sqlite3_column_text(stmt, 0);
            int score = sqlite3_column_int(stmt, 1);
            highScores.push_back(username + ": " + std::to_string(score) + " correct answers");
        }
    }

    sqlite3_finalize(stmt);
    return highScores;
}


std::vector<std::string> StatisticsManager::getUserStatistics(const std::string &username)
{
    std::vector<std::string> stats;

    int correctAnswers = m_database->getNumOfCorrectAnswers(username);
    int totalAnswers = m_database->getNumOfTotalAnswers(username);
    int totalGames = m_database->getNumOfPlayerGames(username);
    float avgAnswerTime = m_database->getPlayerAverageAnswerTime(username);

    stats.push_back("Correct Answers: " + std::to_string(correctAnswers));
    stats.push_back("Total Answers: " + std::to_string(totalAnswers));
    stats.push_back("Total Games: " + std::to_string(totalGames));
    stats.push_back("Average Answer Time: " + std::to_string(avgAnswerTime));

    return stats;
}
