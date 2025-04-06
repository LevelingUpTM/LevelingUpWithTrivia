#include "LoginRequestHandler.h"

#define LOGIN_REQUEST 1
#define SIGNUP_REQUEST 2

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
        // TODO: parse and process login
        result.response = { 0x01 };  // Login success
        result.newHandler = this;
    }
    else if (request.id == SIGNUP_REQUEST)
    {
        // TODO: parse and process signup
        result.response = { 0x02 };  // Signup success
        result.newHandler = this;
    }

    return result;
}
