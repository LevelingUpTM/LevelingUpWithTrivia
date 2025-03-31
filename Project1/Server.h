#pragma once
#include "Communicator.h"
#include <string>
#include <iostream>
#include <thread>
class Server
{
private:
	Communicator m_communicator;

public:
	void run();
};
