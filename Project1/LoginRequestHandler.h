#pragma once
#include "LoginManager.h"
#include "IRequestHandler.h"
#include "RequestInfo.h"
#include "RequestResult.h"
class RequestHandlerFactory;
class LoginRequestHandler : public IRequestHandler
{
public:
    explicit LoginRequestHandler(RequestHandlerFactory& handlerFactory);

    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;

private:
    RequestHandlerFactory& m_handlerFactory;
    LoginManager& m_loginManager;

    RequestResult login(const RequestInfo& request);
    RequestResult signup(const RequestInfo& request);
};
