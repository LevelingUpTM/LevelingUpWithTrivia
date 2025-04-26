#pragma once

#include "IDatabase.h"
#include "LoggedUser.h"
#include <vector>
#include <string>

enum class LoginStatus
{
    SUCCESS,
    USER_NOT_FOUND,
    WRONG_PASSWORD,
    ALREADY_LOGGED_IN
};

enum class SignUpStatus
{
    SUCCESS,
    USER_ALREADY_EXISTS,
    UNKNOWN_ERROR
};

class LoginManager
{
public:
    LoginManager(IDatabase* db);

    LoginStatus login(const std::string& username, const std::string& password);
    SignUpStatus signup(const std::string& username, const std::string& password, const std::string& email);
    void logout(const std::string& username);

private:
    IDatabase* m_database;
    std::vector<LoggedUser> m_loggedUsers;
};
