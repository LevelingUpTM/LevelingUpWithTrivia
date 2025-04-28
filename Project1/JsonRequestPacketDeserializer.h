#pragma once
#include <vector>
#include <string>
#include <chrono>
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


class JsonRequestPacketDeserializer
{
public:
    static LoginRequest deserializeLoginRequest(const vector<unsigned char>& data);
    static SignupRequest deserializeSignUpRequest(const vector<unsigned char>& data);
};
