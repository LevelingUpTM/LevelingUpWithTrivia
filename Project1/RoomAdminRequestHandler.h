#pragma once

#include "IRequestHandler.h"
#include "Room.h"
#include "RoomManager.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"

class RoomAdminRequestHandler : public IRequestHandler
{
public:
    RoomAdminRequestHandler(LoggedUser& user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);

    bool isRequestRelevant(RequestInfo& requestInfo) override;
    RequestResult handleRequest(RequestInfo& requestInfo) override;

private:
    Room m_room;
    LoggedUser m_user;
    RoomManager& m_roomManager;
    RequestHandlerFactory& m_handlerFactory;

    RequestResult closeRoom(RequestInfo& requestInfo);
    RequestResult startGame(RequestInfo& requestInfo);
    RequestResult getRoomState(RequestInfo& requestInfo);
};
