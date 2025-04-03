#include "Server.h"
#include <WinSock2.h>
#include <iostream>
#include <thread>

void Server::run()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    thread serverThread(&Communicator::startHandleRequest, &m_communicator);
    serverThread.detach();

    std::string command;
    while (true)
    {
        std::getline(std::cin, command);
        if (command == "EXIT")
        {
            cout << "Shutting down server...\n";
            WSACleanup();
            break;
        }
    }
}
