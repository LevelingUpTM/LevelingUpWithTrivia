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

    sqlite3 *getDB() const;


private:
    sqlite3* db;
};
