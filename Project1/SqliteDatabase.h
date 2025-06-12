#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include <string>

class SqliteDatabase : public IDatabase
{
public:
    SqliteDatabase();
    ~SqliteDatabase() override;

    bool open() override;
    bool close() override;
    int doesUserExist(std::string username) override;
    int doesPasswordMatch(std::string username, std::string password) override;
    int addNewUser(std::string username, std::string password, std::string email) override;
    std::list<Question> getQuestions(int numOfQuestions) override;

     float getPlayerAverageAnswerTime(const std::string &username) override;
     int getNumOfCorrectAnswers(const std::string &username) override;
     int getNumOfTotalAnswers(const std::string &username) override;
     int getNumOfPlayerGames(const std::string &username) override;
     int getPlayerScore(const std::string &username) override;
     vector<string> getHighScores() override;
     void submitStatistics(const std::string &userName, int correctAnswerCount, int wrongAnswerCount,
                           int avarageAnswerTime) override;

    sqlite3 *getDB() const;


private:
    sqlite3* db;
};
