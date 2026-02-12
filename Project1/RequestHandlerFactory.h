#pragma once
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "GameManager.h"
#include "Game.h"
#include "GameManager.h"
class GameRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class LoggedUser;
class MenuRequestHandler;
class RequestHandlerFactory
{
public:
    explicit RequestHandlerFactory(IDatabase* database);

    LoginRequestHandler* createLoginRequestHandler();
    LoginManager& getLoginManager();
    MenuRequestHandler* createMenuRequestHandler(LoggedUser& user);
    RoomAdminRequestHandler *createRoomAdminRequestHandler(LoggedUser& user, Room &room);
    RoomMemberRequestHandler *createRoomMemberRequestHandler(LoggedUser& user, Room &room);
    GameRequestHandler *createGameRequestHandler(LoggedUser &user);
 

    GameManager &getGameManager();
    RoomManager& getRoomManager();
    StatisticsManager& getStatisticsManager();

private:
    LoginManager m_loginManager;
    IDatabase* m_database;
    RoomManager m_roomManager;
    StatisticsManager m_StatisticsManager;
    GameManager m_gameManager;
};
