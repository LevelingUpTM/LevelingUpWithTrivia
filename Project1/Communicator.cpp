#include "Communicator.h"
#include <WinSock2.h>
#include <iostream>
#include <thread>

const int PORT = 5555;       // Port number to listen 
const int BUFFER_SIZE = 6;  // Size of the buffer for receiving data

void Communicator::bindAndListen()
{
    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (m_serverSocket == INVALID_SOCKET)
    {
        cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);  

    if (bind(m_serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        cerr << "Bind failed\n";
        closesocket(m_serverSocket);
        return;
    }

    if (listen(m_serverSocket, 5) == SOCKET_ERROR)
    {
        cerr << "Listen failed\n";
        closesocket(m_serverSocket);
        return;
    }

    cout << "Server listening on port " << PORT << "...\n";
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
    cout << "New client connected!\n";

    send(clientSocket, "hello", 5, 0);  // Send "hello" to client

    char buffer[BUFFER_SIZE]; 

    while (true)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived <= 0) break;

        buffer[bytesReceived] = '\0';
        cout << "Client: " << buffer << endl;
    }

    closesocket(clientSocket);
}

void Communicator::startHandleRequest()
{
    bindAndListen();

    while (true)
    {
        SOCKET clientSocket = accept(m_serverSocket, nullptr, nullptr);
        if (clientSocket == INVALID_SOCKET) continue;

        thread(&Communicator::handleNewClient, this, clientSocket).detach();
    }
}
