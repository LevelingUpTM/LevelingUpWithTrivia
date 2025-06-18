#include "RoomAdminRequestHandler.h"
#include "statusCodes.h"
#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "MenuRequestHandler.h"
#include "GameRequestHandler.h"
RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser &user, Room &room, RoomManager &roomManager,
                                                 RequestHandlerFactory &handlerFactory)
    : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}


bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo &requestInfo)
{
    return requestInfo.id == CLOSE_ROOM_REQUEST || requestInfo.id == START_GAME_REQUEST ||
           requestInfo.id == GET_ROOM_STATE_REQUEST || requestInfo.id == LOGOUT_REQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo &requestInfo)
{
    if (requestInfo.id == LOGOUT_REQUEST)
        return this->signout(requestInfo);

    switch (requestInfo.id)
    {
    case CLOSE_ROOM_REQUEST:
        return closeRoom(requestInfo);
    case START_GAME_REQUEST:
        return startGame(requestInfo);
    case GET_ROOM_STATE_REQUEST:
        return getRoomState(requestInfo);
    default:
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Invalid request for admin."}), nullptr};
    }
}

RequestResult RoomAdminRequestHandler::signout(RequestInfo request)
{
    m_handlerFactory.getLoginManager().logout(m_user.getUsername());
    return {JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse{SUCCESS}),
            m_handlerFactory.createLoginRequestHandler()};
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo &requestInfo)
{
    m_roomManager.deleteRoom(m_room.getMetadata().id);
    CloseRoomResponse response;
    response.status = 1;

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeCloseRoomResponse(response);
    result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    return result;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo &requestInfo)
{
    StartGameResponse response;
    response.status = 1;

    m_handlerFactory.getGameManager().createGame(m_room); 
    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeStartGameResponse(response);
    result.newHandler = m_handlerFactory.createGameRequestHandler(m_user);
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo &requestInfo)
{
    GetRoomStateResponse response;
    response.status = 1;
    response.hasGameBegun = m_room.getGame() != nullptr;
    response.questionCount = m_room.getMetadata().numOfQuestionsInGame;
    response.answerTimeOut = m_room.getMetadata().timePerQuestion;

    m_handlerFactory.getLoginManager();
    const std::list<LoggedUser*> users = m_room.getAllUsers();    
    std::vector<std::string> usersVector;
    for (LoggedUser *user : users)
    {
        usersVector.push_back(user->getUsername());
    }
    response.players = usersVector;

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeGetRoomStateResponse(response);
    result.newHandler = this;
    return result;
}
