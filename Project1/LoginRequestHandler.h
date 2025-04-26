#pragma once

#include "IRequestHandler.h"
#include "RequestInfo.h"
#include "RequestResult.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
    LoginRequestHandler(RequestHandlerFactory& handlerFactory);

    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;

private:
    RequestHandlerFactory& m_handlerFactory;

    RequestResult login(RequestInfo request);
    RequestResult signup(RequestInfo request);
};
