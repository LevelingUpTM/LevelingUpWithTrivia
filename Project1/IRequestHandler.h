#pragma once

#include "RequestInfo.h"
#include "RequestResult.h"
//
class IRequestHandler
{
public:
    virtual bool isRequestRelevant(RequestInfo request) = 0;
    virtual RequestResult handleRequest(RequestInfo request) = 0;
    virtual ~IRequestHandler() = default;
};
