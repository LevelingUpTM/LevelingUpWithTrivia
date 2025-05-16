#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class LoggedUser;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:
    explicit RequestHandlerFactory(IDatabase* database);

    LoginRequestHandler* createLoginRequestHandler();
    LoginManager& getLoginManager();
    MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();

private:
    LoginManager m_loginManager;
    IDatabase* m_database;
    RoomManager m_roomManager;
    StatisticsManager m_StatisticsManager;
};
