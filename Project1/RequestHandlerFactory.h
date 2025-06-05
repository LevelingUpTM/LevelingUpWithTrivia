#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoggedUser;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:
    explicit RequestHandlerFactory(IDatabase* database);

    LoginRequestHandler* createLoginRequestHandler();
    LoginManager& getLoginManager();
    MenuRequestHandler* createMenuRequestHandler(const LoggedUser& user);
    RoomAdminRequestHandler *createRoomAdminRequestHandler(LoggedUser& user, Room &room);
    RoomMemberRequestHandler *createRoomMemberRequestHandler(LoggedUser& user, Room &room);


    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();

private:
    LoginManager m_loginManager;
    IDatabase* m_database;
    RoomManager m_roomManager;
    StatisticsManager m_StatisticsManager;
};
