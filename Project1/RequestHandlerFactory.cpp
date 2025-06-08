#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : 
    m_loginManager(database), m_database(database), m_StatisticsManager(database)
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

RoomManager &RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager &RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}
