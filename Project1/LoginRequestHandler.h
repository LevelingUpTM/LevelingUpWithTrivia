#pragma once

#include "IRequestHandler.h"
#include "RequestInfo.h"
#include "RequestResult.h"

class LoginRequestHandler : public IRequestHandler
{
public:
    bool isRequestRelevant(RequestInfo request) override;
    RequestResult handleRequest(RequestInfo request) override;
};