#pragma once

#include <vector>
#include <ctime>

using Byte = unsigned char;
using RequestId = unsigned int;

struct RequestInfo
{
    RequestId id;
    time_t receivalTime;
    std::vector<Byte> buffer;
};
