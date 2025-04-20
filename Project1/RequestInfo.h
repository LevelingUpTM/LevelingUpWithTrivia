#pragma once

#include <vector>
//#include <ctime>
#include <chrono>

using Byte = unsigned char;
using RequestId = unsigned int;

struct RequestInfo
{
    RequestId id;
    std::chrono::time_point<std::chrono::system_clock> receivalTime;
    std::vector<Byte> buffer;
};
