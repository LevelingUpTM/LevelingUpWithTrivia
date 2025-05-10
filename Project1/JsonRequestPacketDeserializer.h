#pragma once
#include <vector>
#include <string>
#include "json.hpp"

using std::string;
using std::vector;
using json = nlohmann::json;

struct LoginRequest
{
    string username;
    string password;
};

struct SignupRequest
{
    string username;
    string password;
    string email;
};

struct GetPlayersInRoomRequest
{
    unsigned int roomId;
};

struct JoinRoomRequest
{
    unsigned int roomId;
};

struct CreateRoomRequest
{
    string roomName;
    unsigned int maxUsers;
    unsigned int questionCount;
    unsigned int answerTimeout;
};

class JsonRequestPacketDeserializer
{
public:
    static LoginRequest deserializeLoginRequest(const vector<unsigned char>& data);
    static SignupRequest deserializeSignUpRequest(const vector<unsigned char>& data);
    static GetPlayersInRoomRequest deserializeGetPlayersRequest(const vector<unsigned char>& data);
    static JoinRoomRequest deserializeJoinRoomRequest(const vector<unsigned char>& data);
    static CreateRoomRequest deserializeCreateRoomRequest(const vector<unsigned char>& data);
};
