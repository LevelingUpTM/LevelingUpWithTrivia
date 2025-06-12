#include "JsonResponsePacketSerializer.h"
#include "statusCodes.h"

vector<Byte> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(LOGOUT_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(JOIN_ROOM_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse &response)
{
    json j;
    j["status"] = response.status;
    j["roomId"] = response.roomId;
    return createBuffer(CREATE_ROOM_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeGetRoomsResponse(const GetRoomsResponse &response)
{
    json j;
    j["status"] = response.status;
    j["rooms"] = json::array();
    for (const auto &room : response.rooms)
    {
        json roomJson;
        roomJson["id"] = room.id;
        roomJson["name"] = room.name;
        roomJson["maxPlayers"] = room.maxPlayers;
        roomJson["questionCount"] = room.numOfQuestionsInGame;
        roomJson["timePerQuestion"] = room.timePerQuestion;
        roomJson["isActive"] = room.isActive;
        j["rooms"].push_back(roomJson);
    }
    return createBuffer(GET_ROOMS_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(
    const GetPlayersInRoomResponse &response)
{
    json j;
    j["players"] = response.players;
    return createBuffer(GET_PLAYERS_IN_ROOM_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeHighScoreResponse(const GetHighScoreResponse &response)
{
    json j;
    j["status"] = response.status;
    j["statistics"] = response.statistics;
    return createBuffer(GET_HIGHSCORE_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializePersonalStatsResponse(
    const GetPersonalStatsResponse &response)
{
    json j;
    j["status"] = response.status;
    j["statistics"] = response.statistics;
    return createBuffer(GET_PERSONAL_STATS_RESPONSE, j);
}

std::vector<Byte> JsonResponsePacketSerializer::serializeCloseRoomResponse(const CloseRoomResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(CLOSE_ROOM_RESPONSE, j);
}

std::vector<Byte> JsonResponsePacketSerializer::serializeStartGameResponse(const StartGameResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(START_GAME_RESPONSE, j);
}

std::vector<Byte> JsonResponsePacketSerializer::serializeGetRoomStateResponse(
    const GetRoomStateResponse &response)
{
    json j;
    j["status"] = response.status;
    j["answerTimeOut"] = response.answerTimeOut;
    j["hasGameBegun"] = response.hasGameBegun;
    j["players"] = response.players;
    j["questionCount"] = response.questionCount;
    return createBuffer(GET_ROOM_STATE_RESPONSE, j);
}

std::vector<Byte> JsonResponsePacketSerializer::serializeLeaveRoomResponse(const LeaveRoomResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(LEAVE_ROOM_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(LOGIN_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeSignUpResponse(const SignupResponse &response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(SIGNUP_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse &response)
{
    json j;
    j["message"] = response.message;
    return createBuffer(ERROR_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeGetGameResultsResponse(const GetGameResultsResponse &response)
{
    json j;
    j["status"] = response.status;
    j["results"] = json::array();

    for (const auto &playerResult : response.result)
    {
        json pr;
        pr["username"] = playerResult.username;
        pr["correctAnswerCount"] = playerResult.correctAnswerCount;
        pr["wrongAnswerCount"] = playerResult.wrongAnswerCount;
        pr["averageAnswerTime"] = playerResult.averageAnswerTime;
        j["results"].push_back(pr);
    }

    return createBuffer(GET_GAME_RESULTS_RESPONSE, j);
}


vector<Byte> JsonResponsePacketSerializer::serializeSubmitAnswerResponse(const SubmitAnswerResponse &response)
{
    json j;
    j["status"] = response.status;
    j["correctAnswerId"] = response.correctAnswerId;
    return createBuffer(SUBMIT_ANSWER_RESPONSE, j);
}

vector<Byte> JsonResponsePacketSerializer::serializeGetQuestionResponse(const GetQuestionResponse &response)
{
    json j;
    j["status"] = response.status;
    j["question"] = response.question;
    j["answers"] = json::object();

    for (auto it = response.answers.begin(); it != response.answers.end(); ++it)
    {
        j["answers"][std::to_string(it->first)] = it->second;
    }

    return createBuffer(GET_QUESTION_RESPONSE, j);
}


vector<Byte> JsonResponsePacketSerializer::serializeLeaveGameResponse(const LeaveGameResponse& response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(LEAVE_GAME_RESPONSE, j);
}


vector<Byte> JsonResponsePacketSerializer::createBuffer(const Byte code, const json &jsonResponse)
{
    string jsonStr = jsonResponse.dump(); // Convert JSON to string
    const size_t size = jsonStr.size();

    vector<Byte> buffer;
    buffer.push_back(code); // First byte is the response code

    // Add 4 bytes for message size
    buffer.push_back((size >> 24) & 0xFF);
    buffer.push_back((size >> 16) & 0xFF);
    buffer.push_back((size >> 8) & 0xFF);
    buffer.push_back(size & 0xFF);

    // Add the JSON string data
    buffer.insert(buffer.end(), jsonStr.begin(), jsonStr.end());

    return buffer;
}
