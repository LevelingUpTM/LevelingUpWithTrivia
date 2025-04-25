#include "LoginRequestHandler.h"

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
    RequestResult result;

    if (!isRequestRelevant(request))
    {
        result.response = { 0xFF };  // Error code
        result.newHandler = this;
        return result;
    }

    if (request.id == LOGIN_REQUEST)
    {
        result.response = { 0x01 };  // Login success
        result.newHandler = this;
    }
    else if (request.id == SIGNUP_REQUEST)
    {
        result.response = { 0x02 };  // Signup success
        result.newHandler = this;
    }

    return result;
}

RequestResult LoginRequestHandler::login(RequestInfo request)
{
    return { { 0x01 }, this }; 
}

RequestResult LoginRequestHandler::signup(RequestInfo request)
{
    return { { 0x02 }, this };
}