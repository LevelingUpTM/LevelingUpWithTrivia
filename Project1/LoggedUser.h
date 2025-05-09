#pragma once
#include <string>

class LoggedUser
{
public:
    explicit LoggedUser(const std::string& username);
    std::string getUsername() const;

private:
    std::string m_username;
};
