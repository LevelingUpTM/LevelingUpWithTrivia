#include "RoomAdminRequestHandler.h"
#include "statusCodes.h"
#include "JsonResponsePacketSerializer.h"
#include "json.hpp"
#include "MenuRequestHandler.h"
RoomAdminRequestHandler::RoomAdminRequestHandler(LoggedUser &user, Room &room, RoomManager &roomManager,
                                                 RequestHandlerFactory &handlerFactory)
    : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}


bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo &requestInfo)
{
    return requestInfo.id == CLOSE_ROOM_REQUEST || requestInfo.id == START_GAME_REQUEST ||
           requestInfo.id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo &requestInfo)
{
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

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeStartGameResponse(response);
    result.newHandler = this;
    return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo &requestInfo)
{
    GetRoomStateResponse response;
    response.status = 1;
    response.hasGameBegun = false; // Game logic not implemented yet
    response.questionCount = m_room.getMetadata().numOfQuestionsInGame;
    response.answerTimeOut = m_room.getMetadata().timePerQuestion;

    m_handlerFactory.getLoginManager();
    std::list<std::string> usersList = m_room.getAllUsers();
    std::vector<std::string> users(usersList.begin(), usersList.end());
    response.players = users;

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeGetRoomStateResponse(response);
    result.newHandler = this;
    return result;
}
