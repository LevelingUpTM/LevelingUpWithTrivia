#include "Communicator.h"

void Communicator::bindAndListen()
{
}

void Communicator::handleNewClient(SOCKET socket)
{
	std::cout << "New client connected: " << socket << std::endl;
	m_clients[socket] = nullptr;
}

void Communicator::startHandleRequest()
{
	bindAndListen();

	while (true)
	{
        sockaddr_in clientAddr = {};
        int addrLen = sizeof(clientAddr);
        SOCKET clientSocket = accept(m_serverSocket, (sockaddr*)&clientAddr, &addrLen);

        if (clientSocket == INVALID_SOCKET)
        {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "New client connected!\n";

        std::thread clientThread(&Communicator::handleNewClient, this, clientSocket);
        clientThread.detach();
	}
}
