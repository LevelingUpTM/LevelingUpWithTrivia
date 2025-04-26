#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#define LOGIN_REQUEST 1
#define SIGNUP_REQUEST 2

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory)
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo request)
{
    return request.id == LOGIN_REQUEST || request.id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo request)
{
    if (!isRequestRelevant(request))
    {
        return { { 0xFF }, this };
    }

    if (request.id == LOGIN_REQUEST)
    {
        return login(request);
    }
    else if (request.id == SIGNUP_REQUEST)
    {
        return signup(request);
    }

    return { { 0xFF }, this };
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
    JsonRequestPacketDeserializer deserializer;
    LoginRequest loginData = deserializer.deserializeLoginRequest(request.buffer);

    LoginStatus status = m_handlerFactory.getLoginManager().login(loginData.username, loginData.password);

    LoginResponse response;
    RequestResult result;

    switch (status)
    {
    case LoginStatus::SUCCESS:
        response.status = 1;
        result.newHandler = this;
        break;
    case LoginStatus::USER_NOT_FOUND:
        response.status = 2;
        result.newHandler = this;
        break;
    case LoginStatus::WRONG_PASSWORD:
        response.status = 3;
        result.newHandler = this;
        break;
    case LoginStatus::ALREADY_LOGGED_IN:
        response.status = 4;
        result.newHandler = this;
        break;
    }

    JsonResponsePacketSerializer serializer;
    result.response = serializer.serializeLoginResponse(response);
    return result;
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
    JsonRequestPacketDeserializer deserializer;
    SignupRequest signupData = deserializer.deserializeSignUpRequest(request.buffer);

    SignUpStatus status = m_handlerFactory.getLoginManager().signup(signupData.username, signupData.password, signupData.email);

    SignupResponse response;
    RequestResult result;

    switch (status)
    {
    case SignUpStatus::SUCCESS:
        response.status = 1;
        result.newHandler = this;
        break;
    case SignUpStatus::USER_ALREADY_EXISTS:
        response.status = 2;
        result.newHandler = this;
        break;
    case SignUpStatus::UNKNOWN_ERROR:
        response.status = 3;
        result.newHandler = nullptr;
        break;
    }

    JsonResponsePacketSerializer serializer;
    result.response = serializer.serializeSignUpResponse(response);
    return result;
}