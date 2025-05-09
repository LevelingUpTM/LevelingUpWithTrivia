#include "LoginManager.h"

LoginManager::LoginManager(IDatabase* db)
    : m_database(db)
{
}

LoginStatus LoginManager::login(const std::string& username, const std::string& password)
{
    // Already logged in?
    for (const LoggedUser& user : m_loggedUsers)
    {
        if (user.getUsername() == username)
        {
            return LoginStatus::ALREADY_LOGGED_IN;
        }
    }

    // Check if user exists
    if (!m_database->doesUserExist(username))
    {
        return LoginStatus::USER_NOT_FOUND;
    }

    // Check password match
    if (!m_database->doesPasswordMatch(username, password))
    {
        return LoginStatus::WRONG_PASSWORD;
    }

    // Add to logged users
    m_loggedUsers.push_back(LoggedUser(username));
    return LoginStatus::SUCCESS;
}

SignUpStatus LoginManager::signup(const std::string& username, const std::string& password, const std::string& email) const
{
    if (m_database->doesUserExist(username))
    {
        return SignUpStatus::USER_ALREADY_EXISTS;
    }

    if (!m_database->addNewUser(username, password, email))
    {
        return SignUpStatus::UNKNOWN_ERROR;
    }

    return SignUpStatus::SUCCESS;
}

void LoginManager::logout(const std::string& username)
{
    for (auto it = m_loggedUsers.begin(); it != m_loggedUsers.end(); ++it)
    {
        if (it->getUsername() == username)
        {
            m_loggedUsers.erase(it);
            return;
        }
    }
}
