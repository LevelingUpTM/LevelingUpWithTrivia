#include "MenuRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "StatusCodes.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

MenuRequestHandler::MenuRequestHandler(const LoggedUser& user, RoomManager &roomManager, StatisticsManager &statisticsManager, RequestHandlerFactory &handlerFactory)
    : m_user(user), m_roomManager(roomManager), m_statisticsManager(statisticsManager), m_handlerFactory(handlerFactory)
{
}

bool MenuRequestHandler::isRequestRelevant(RequestInfo& request)
{
    return request.id == LOGOUT_REQUEST || request.id == GET_ROOMS_REQUEST ||
           request.id == GET_PLAYERS_IN_ROOM_REQUEST || request.id == JOIN_ROOM_REQUEST ||
           request.id == CREATE_ROOM_REQUEST || request.id == GET_HIGHSCORE_REQUEST ||
           request.id == GET_PERSONAL_STATS_REQUEST;
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo& request)
{
    switch (request.id)
    {
    case LOGOUT_REQUEST:
        return this->signout(request);
    case GET_ROOMS_REQUEST:
        return this->getRooms(request);
    case GET_PLAYERS_IN_ROOM_REQUEST:
        return this->getPlayersInRoom(request);
    case JOIN_ROOM_REQUEST:
        return this->joinRoom(request);
    case CREATE_ROOM_REQUEST:
        return this->createRoom(request);
    case GET_HIGHSCORE_REQUEST:
        return this->getHighScore(request);
    case GET_PERSONAL_STATS_REQUEST:
        return this->getPersonalStats(request);
    default:
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Invalid request"}), nullptr};
    }
}

RequestResult MenuRequestHandler::signout(RequestInfo request)
{
    m_handlerFactory.getLoginManager().logout(m_user.getUsername());

return {JsonResponsePacketSerializer::serializeLogoutResponse(LogoutResponse{SUCCESS}),
            m_handlerFactory.createLoginRequestHandler()};
}

RequestResult MenuRequestHandler::getRooms(RequestInfo request)
{
    std::vector<RoomData> rooms = m_roomManager.getRooms();
    GetRoomsResponse response{SUCCESS, rooms};

    return {JsonResponsePacketSerializer::serializeGetRoomsResponse(response), this};
}

RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo request)
{
    GetPlayersInRoomRequest data = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(request.buffer);
    try
    {
        std::list<std::string> users = m_roomManager.getRoom(data.roomId).getAllUsers();
        std::vector<std::string> usersVector(users.begin(), users.end());
        return {JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(GetPlayersInRoomResponse{usersVector}),
                this};
    }
    catch (...)
    {
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Room not found"}), this};
    }
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo request)
{
    JoinRoomRequest data = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(request.buffer);
    try
    {
        Room &room = m_roomManager.getRoom(data.roomId);
        room.addUser(m_user);
        return {JsonResponsePacketSerializer::serializeJoinRoomResponse(JoinRoomResponse{SUCCESS}),
                m_handlerFactory.createRoomMemberRequestHandler(m_user, room)};
    }
    catch (...)
    {
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Failed to join room"}), this};
    }
}

RequestResult MenuRequestHandler::createRoom(RequestInfo request)
{
    CreateRoomRequest data = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(request.buffer);
    RoomData rd;
    rd.id = m_roomManager.getNextRoomId();
    rd.name = data.roomName;
    rd.maxPlayers = data.maxUsers;
    rd.timePerQuestion = data.answerTimeout;
    rd.numOfQuestionsInGame = data.questionCount;
    rd.isActive = false;

    Room& room = m_roomManager.createRoom(m_user, rd);
    return {JsonResponsePacketSerializer::serializeCreateRoomResponse(CreateRoomResponse{SUCCESS, room.getMetadata().id}),
        m_handlerFactory.createRoomAdminRequestHandler(m_user, room)};
}

RequestResult MenuRequestHandler::getHighScore(RequestInfo request)
{
    std::vector<std::string> highScores = m_statisticsManager.getHighScore();
    return {JsonResponsePacketSerializer::serializeHighScoreResponse(GetHighScoreResponse{SUCCESS, highScores}), this};
}

RequestResult MenuRequestHandler::getPersonalStats(RequestInfo request)
{
    std::vector<std::string> stats = m_statisticsManager.getUserStatistics(m_user.getUsername());
    return {JsonResponsePacketSerializer::serializePersonalStatsResponse(GetPersonalStatsResponse{SUCCESS, stats}), this};
}
