#pragma once
#include <vector>
#include <string>
#include "json.hpp"

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

class JsonResponsePacketSerializer
{
public:
    static vector<unsigned char> serializeLoginResponse(const LoginResponse& response);
    static vector<unsigned char> serializeSignUpResponse(const SignupResponse& response);
    static vector<unsigned char> serializeErrorResponse(const ErrorResponse& response);

private:
    static vector<unsigned char> createBuffer(unsigned char code, const json& jsonResponse);
};
