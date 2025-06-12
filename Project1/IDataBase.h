#pragma once

#include <string>
#include <list>
#include "sqlite3.h"
#include "Question.h"

using std::list;

class IDatabase
{
public:
    virtual ~IDatabase() = default;

    virtual bool open() = 0;
    virtual bool close() = 0;
    virtual int doesUserExist(string username) = 0;
    virtual int doesPasswordMatch(string username, string password) = 0;
    virtual int addNewUser(string username, string password, string email) = 0;
    virtual std::list<Question> getQuestions(int numOfQuestions) = 0;
    virtual sqlite3* getDB() const = 0;
    virtual void submitStatistics(const std::string &userName, int correctAnswerCount, int wrongAnswerCount,
                                  int avarageAnswerTime) = 0;


    virtual float getPlayerAverageAnswerTime(const std::string &username) = 0;
    virtual int getNumOfCorrectAnswers(const std::string &username) = 0;
    virtual int getNumOfTotalAnswers(const std::string &username) = 0;
    virtual int getNumOfPlayerGames(const std::string &username) = 0;
    virtual int getPlayerScore(const std::string &username) = 0;
    virtual vector<string> getHighScores() = 0;

 

};