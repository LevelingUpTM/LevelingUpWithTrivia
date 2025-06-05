#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#define LOGIN_REQUEST 1
#define SIGNUP_REQUEST 2

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory& handlerFactory)
    : m_handlerFactory(handlerFactory),
    m_loginManager(handlerFactory.getLoginManager())
{
}

bool LoginRequestHandler::isRequestRelevant(RequestInfo& request)
{
    return request.id == LOGIN_REQUEST || request.id == SIGNUP_REQUEST;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo& request)
{
    if (!isRequestRelevant(request))
    {
        return { { 0xFF }, this };
    }

    if (request.id == LOGIN_REQUEST)
    {
        return login(request);
    }
    if (request.id == SIGNUP_REQUEST)
    {
        return signup(request);
    }

    return { { 0xFF }, this };
}

RequestResult LoginRequestHandler::login(const RequestInfo& request)
{
    const LoginRequest loginData = JsonRequestPacketDeserializer::deserializeLoginRequest(request.buffer);

    const LoginStatus status = m_handlerFactory.getLoginManager().login(loginData.username, loginData.password);

    LoginResponse response{};
    RequestResult result;

    switch (status)
    {
    case LoginStatus::SUCCESS:
        response.status = 1;
        result.newHandler =
            new MenuRequestHandler(m_loginManager.usernameToUser(loginData.username), m_handlerFactory.getRoomManager(),
                                   m_handlerFactory.getStatisticsManager(), m_handlerFactory);
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
    default:
        throw std::logic_error("Unexpected login status");
    }

    result.response = JsonResponsePacketSerializer::serializeLoginResponse(response);
    return result;
}

RequestResult LoginRequestHandler::signup(const RequestInfo& request)
{
    const SignupRequest signupData = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer);

    const SignUpStatus status = m_handlerFactory.getLoginManager().signup(signupData.username, signupData.password, signupData.email);

    SignupResponse response{};
    RequestResult result;
    result.newHandler = this;

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
        result.newHandler = this;
        break;
    }

    result.response = JsonResponsePacketSerializer::serializeSignUpResponse(response);
    return result;
}