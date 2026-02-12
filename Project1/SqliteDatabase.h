#pragma once

#include "IDatabase.h"
#include "sqlite3.h"
#include <string>

using std::string;
using std::vector;

class SqliteDatabase : public IDatabase
{
public:
    SqliteDatabase();
    ~SqliteDatabase() override;

    bool open() override;
    bool close() override;
    int doesUserExist(string username) override;
    int doesPasswordMatch(string username, string password) override;
    int addNewUser(string username, string password, string email) override;
    std::list<Question> getQuestions(int numOfQuestions) override;

     float getPlayerAverageAnswerTime(const string &username) override;
     int getNumOfCorrectAnswers(const string &username) override;
     int getNumOfTotalAnswers(const string &username) override;
     int getNumOfPlayerGames(const string &username) override;
     int getPlayerScore(const string &username) override;
     vector<string> getHighScores() override;
     void submitStatistics(const string &userName, int correctAnswerCount, int wrongAnswerCount,
                           int avarageAnswerTime) override;

    sqlite3 *getDB() const;


private:
    sqlite3* db;
};
