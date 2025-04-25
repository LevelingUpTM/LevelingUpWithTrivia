#pragma once
#include <WinSock2.h>
#include <map>
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::cerr;
using std::thread;

class Communicator
{
private:
	SOCKET m_serverSocket;
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory& m_handlerFactory;


	void bindAndListen();
	void handleNewClient(SOCKET clientSocket);

public:
	void startHandleRequest();
};
