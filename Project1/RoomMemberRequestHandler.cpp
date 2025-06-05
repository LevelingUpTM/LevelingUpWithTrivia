#include "RoomMemberRequestHandler.h"
#include "JsonResponsePacketSerializer.h"
#include "statusCodes.h"
#include "MenuRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(LoggedUser& user, Room& room, RoomManager &roomManager,
                                                   RequestHandlerFactory &handlerFactory)
    : m_user(user), m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo &requestInfo)
{
    return requestInfo.id == LEAVE_ROOM_REQUEST || requestInfo.id == GET_ROOM_STATE_REQUEST;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo &requestInfo)
{
    switch (requestInfo.id)
    {
    case LEAVE_ROOM_REQUEST:
        return leaveRoom(requestInfo);
    case GET_ROOM_STATE_REQUEST:
        return getRoomState(requestInfo);
    default:
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Invalid request for member."}), nullptr}; 
    }
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
    m_room.removeUser(m_user.getUsername());

    LeaveRoomResponse response;
    response.status = 1;

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeLeaveRoomResponse(response);
    result.newHandler = m_handlerFactory.createMenuRequestHandler(m_user);
    return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
    GetRoomStateResponse response;
    response.status = 1;
    response.hasGameBegun = false;

    std::vector<std::string> users(m_room.getAllUsers().begin(), m_room.getAllUsers().end());
    response.players = users;

    RequestResult result;
    result.response = JsonResponsePacketSerializer::serializeGetRoomStateResponse(response);
    result.newHandler = nullptr;
    return result;
}
