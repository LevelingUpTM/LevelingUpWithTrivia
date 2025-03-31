#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include <utility>
#include <iostream>
#include <thread>

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	void bindAndListen();
	void handleNewClient(SOCKET);

public:
	void startHandleRequest();
};
