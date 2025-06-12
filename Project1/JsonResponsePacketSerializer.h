#pragma once
#include <vector>
#include <string>
#include "json.hpp"
#include "RoomData.h"

using json = nlohmann::json;
using std::vector;
using std::string;
using std::map;

using Byte = unsigned char;

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
    unsigned int roomId;
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

struct CloseRoomResponse
{
    unsigned int status;
};

struct StartGameResponse
{
    unsigned int status;
};

struct GetRoomStateResponse
{
    unsigned int status;
    bool hasGameBegun;
    vector<string> players;
    unsigned int questionCount;
    unsigned int answerTimeOut;
};

struct LeaveRoomResponse
{
    unsigned int status;
};


struct LeaveGameResponse
{
    unsigned int status;
};

struct GetQuestionResponse
{
    unsigned int status;
    string question;
    map<unsigned int, string> answers;
};

struct PlayerResults
{
    string username;
    unsigned int correctAnswerCount;
    unsigned int wrongAnswerCount;
    unsigned int averageAnswerTime;
};

struct GetGameResultsResponse
{
    unsigned int status;
    vector<PlayerResults> result;
};


class JsonResponsePacketSerializer
{
public:
    static vector<Byte> serializeSignUpResponse(const SignupResponse& response);
    static vector<Byte> serializeErrorResponse(const ErrorResponse& response);
    static vector<Byte> serializeLoginResponse(const LoginResponse& response);
    static std::vector<Byte> serializeLogoutResponse(const LogoutResponse& response);
    static std::vector<Byte> serializeJoinRoomResponse(const JoinRoomResponse& response);
    static std::vector<Byte> serializeCreateRoomResponse(const CreateRoomResponse& response);
    static std::vector<Byte> serializeGetRoomsResponse(const GetRoomsResponse& response);
    static std::vector<Byte> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& response);
    static std::vector<Byte> serializeHighScoreResponse(const GetHighScoreResponse& response);
    static std::vector<Byte> serializePersonalStatsResponse(const GetPersonalStatsResponse& response);
    static std::vector<Byte> serializeCloseRoomResponse(const CloseRoomResponse &response);
    static std::vector<Byte> serializeStartGameResponse(const StartGameResponse &response);
    static std::vector<Byte> serializeGetRoomStateResponse(const GetRoomStateResponse &response);
    static std::vector<Byte> serializeLeaveRoomResponse(const LeaveRoomResponse &response);

private:
    static vector<Byte> createBuffer(const Byte code, const json &jsonResponse);
};
