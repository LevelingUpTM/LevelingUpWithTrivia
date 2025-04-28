#pragma once

#include <vector>

using Byte = unsigned char;

class IRequestHandler;

struct RequestResult
{
    std::vector<Byte> response;
    IRequestHandler* newHandler;
};
