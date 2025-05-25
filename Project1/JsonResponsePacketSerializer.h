#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"

using json = nlohmann::json;
using std::vector;
using std::string;

struct LoginResponse
{
    unsigned int status;
};

struct SignupResponse
{
    unsigned int status;
};

struct ErrorResponse
{
    string message;
};

struct LogoutResponse
{
    unsigned int status;
};

struct JoinRoomResponse
{
    unsigned int status;
};

struct CreateRoomResponse
{
    unsigned int status;
};

struct GetRoomsResponse
{
    unsigned int status;
    std::vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
    std::vector<std::string> players;
};

struct GetHighScoreResponse
{
    unsigned int status;
    std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse
{
    unsigned int status;
    std::vector<std::string> statistics;
};

struct LogoutResponse
{
    unsigned int status;
};
class JsonResponsePacketSerializer
{
public:
    static vector<unsigned char> serializeLoginResponse(const LoginResponse& response);
    static vector<unsigned char> serializeSignUpResponse(const SignupResponse& response);
    static vector<unsigned char> serializeErrorResponse(const ErrorResponse& response);
    static std::vector<unsigned char> serializeLogoutResponse(const LogoutResponse& response);
    static std::vector<unsigned char> serializeJoinRoomResponse(const JoinRoomResponse& response);
    static std::vector<unsigned char> serializeCreateRoomResponse(const CreateRoomResponse& response);
    static std::vector<unsigned char> serializeGetRoomsResponse(const GetRoomsResponse& response);
    static std::vector<unsigned char> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response);
    static std::vector<unsigned char> serializeHighScoreResponse(const GetHighScoreResponse& response);
    static std::vector<unsigned char> serializePersonalStatsResponse(const GetPersonalStatsResponse& response);
    static std::vector<unsigned char> serializeLogoutResponse(const LogoutResponse& response);

private:
    static vector<unsigned char> createBuffer(unsigned char code, const json& jsonResponse);
};
