#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : 
    m_loginManager(database), m_database(database), m_StatisticsManager(database), m_gameManager(database)
{
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
    return new LoginRequestHandler(*this);
}

LoginManager& RequestHandlerFactory::getLoginManager()
{
    return m_loginManager;
}

MenuRequestHandler *RequestHandlerFactory::createMenuRequestHandler(LoggedUser& user)
{
    return new MenuRequestHandler(user, getRoomManager(), getStatisticsManager(), *this);
}

RoomAdminRequestHandler *RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser& user, Room &room)
{
    return new RoomAdminRequestHandler(user, room, m_roomManager, *this);
}

RoomMemberRequestHandler *RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser& user, Room &room)
{
    return new RoomMemberRequestHandler(user, room, m_roomManager, *this);
}

GameRequestHandler *RequestHandlerFactory::createGameRequestHandler(LoggedUser &user)
{
    Game *game = m_gameManager.getGameByUser(user);
    return new GameRequestHandler(*game, user, m_gameManager, *this);
}


GameManager &RequestHandlerFactory::getGameManager()
{
    return m_gameManager;
}

RoomManager &RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager &RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}
