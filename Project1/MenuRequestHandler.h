#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
#include "RoomManager.h"
#include "StatisticsManager.h"

class MenuRequestHandler : public IRequestHandler
{
  public:
    MenuRequestHandler(LoggedUser& user, RoomManager &roomManager, StatisticsManager &statisticsManager,
                       RequestHandlerFactory &handlerFactory);

    bool isRequestRelevant(RequestInfo& request) override;
    RequestResult handleRequest(RequestInfo& request) override;

  private:
    RequestResult signout(RequestInfo request);
    RequestResult getRooms(RequestInfo request);
    RequestResult getPlayersInRoom(RequestInfo request);
    RequestResult joinRoom(RequestInfo request);
    RequestResult createRoom(RequestInfo request);
    RequestResult getPersonalStats(RequestInfo request);
    RequestResult getHighScore(RequestInfo request);

    LoggedUser& m_user;
    RoomManager &m_roomManager;
    StatisticsManager &m_statisticsManager;
    RequestHandlerFactory &m_handlerFactory;
};
