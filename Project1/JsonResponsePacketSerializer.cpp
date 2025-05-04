#include "JsonResponsePacketSerializer.h"

vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse& response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(4, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse& response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(7, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse& response)
{
    json j;
    j["status"] = response.status;
    return createBuffer(8, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomsResponse(const GetRoomsResponse& response)
{
    json j;
    j["status"] = response.status;
    j["rooms"] = json::array();
    for (const auto& room : response.rooms)
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
    return createBuffer(5, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response)
{
    json j;
    j["players"] = response.players;
    return createBuffer(6, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializeHighScoreResponse(const GetHighScoreResponse& response)
{
    json j;
    j["status"] = response.status;
    j["statistics"] = response.statistics;
    return createBuffer(9, j);
}

vector<unsigned char> JsonResponsePacketSerializer::serializePersonalStatsResponse(const GetPersonalStatsResponse& response)
{
    json j;
    j["status"] = response.status;
    j["statistics"] = response.statistics;
    return createBuffer(10, j);
}


vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse& response)
{
    json jsonResponse;
    jsonResponse["status"] = response.status;
    return createBuffer(1, jsonResponse);  // 1 = Login response code
}

vector<unsigned char> JsonResponsePacketSerializer::serializeSignUpResponse(const SignupResponse& response)
{
    json jsonResponse;
    jsonResponse["status"] = response.status;
    return createBuffer(2, jsonResponse);  // 2 = Signup response code
}

vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse& response)
{
    json jsonResponse;
    jsonResponse["message"] = response.message;
    return createBuffer(3, jsonResponse);  // 3 = Error response code
}

vector<unsigned char> JsonResponsePacketSerializer::createBuffer(unsigned char code, const json& jsonResponse)
{
    string jsonStr = jsonResponse.dump();  // Convert JSON to string
    size_t size = jsonStr.size();

    vector<unsigned char> buffer;
    buffer.push_back(code); // First byte is the response code

    // Add 4 bytes for message size (big-endian format)
    buffer.push_back((size >> 24) & 0xFF);
    buffer.push_back((size >> 16) & 0xFF);
    buffer.push_back((size >> 8) & 0xFF);
    buffer.push_back(size & 0xFF);

    // Add the JSON string data
    buffer.insert(buffer.end(), jsonStr.begin(), jsonStr.end());

    return buffer;
}
