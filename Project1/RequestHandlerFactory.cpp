#include "RequestHandlerFactory.h"

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

MenuRequestHandler *RequestHandlerFactory::createMenuRequestHandler(LoggedUser user)
{
    return new MenuRequestHandler(user, *this);
}

RoomManager &RequestHandlerFactory::getRoomManager()
{
    return m_roomManager;
}

StatisticsManager &RequestHandlerFactory::getStatisticsManager()
{
    return m_StatisticsManager;
}
