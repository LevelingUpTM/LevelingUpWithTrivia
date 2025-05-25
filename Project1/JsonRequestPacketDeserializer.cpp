#include "JsonRequestPacketDeserializer.h"
LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<unsigned char>& data)
{
    std::string jsonStr(data.begin(), data.end());
    json jsonObj = json::parse(jsonStr);
    LoginRequest request;
    request.username = jsonObj["username"];
    request.password = jsonObj["password"];
    return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const vector<unsigned char>& data)
{
    std::string jsonStr(data.begin(), data.end());
    json jsonObj = json::parse(jsonStr);
    SignupRequest request;
    request.username = jsonObj["username"];
    request.password = jsonObj["password"];
    request.email = jsonObj["email"];
    return request;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(const vector<unsigned char>& data)
{
    std::string jsonStr(data.begin(), data.end());
    json jsonObj = json::parse(jsonStr);
    GetPlayersInRoomRequest request{};
    request.roomId = jsonObj["roomId"];
    return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const vector<unsigned char>& data)
{
    std::string jsonStr(data.begin(), data.end());
    json jsonObj = json::parse(jsonStr);
    JoinRoomRequest request{};
    request.roomId = jsonObj["roomId"];
    return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const vector<unsigned char>& data)
{
    std::string jsonStr(data.begin(), data.end());
    json jsonObj = json::parse(jsonStr);
    CreateRoomRequest request;
    request.roomName = jsonObj["roomName"];
    request.maxUsers = jsonObj["maxUsers"];
    request.questionCount = jsonObj["questionCount"];
    request.answerTimeout = jsonObj["answerTimeout"];
    return request;
}

LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(const vector<unsigned char> &data)
{
    json jsonObj = json::parse(data.begin(), data.end());
    LogoutRequest request;
    request.username = jsonObj["username"];
    return request;
}
