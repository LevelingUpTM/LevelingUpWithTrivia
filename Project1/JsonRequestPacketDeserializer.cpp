#include "JsonRequestPacketDeserializer.h"
#include <iostream>
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
