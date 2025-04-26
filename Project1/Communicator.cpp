#include "Communicator.h"
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include "LoginRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#pragma comment(lib, "Ws2_32.lib")

const int PORT = 5555;       // Port number to listen 

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
    std::cout << "New client connected!\n";

    char headerBuffer[5]; // 1 byte for code + 4 bytes for message length

    IRequestHandler* handler = m_handlerFactory.createLoginRequestHandler();

    while (true)
    {
        // Step 1: Receive header (1 byte code + 4 bytes length)
        int bytesReceived = recv(clientSocket, headerBuffer, 5, 0);
        if (bytesReceived != 5)
        {
            std::cout << "Client disconnected or error receiving header\n";
            break;
        }

        // Extract message code and length
        unsigned char code = headerBuffer[0];
        int length =
            ((unsigned char)headerBuffer[1] << 24) |
            ((unsigned char)headerBuffer[2] << 16) |
            ((unsigned char)headerBuffer[3] << 8) |
            (unsigned char)headerBuffer[4];

        // Step 2: Receive the JSON message body
        std::vector<unsigned char> messageBuffer(length);
        int totalBytesReceived = 0;

        while (totalBytesReceived < length)
        {
            int chunk = recv(clientSocket, reinterpret_cast<char*>(&messageBuffer[totalBytesReceived]), length - totalBytesReceived, 0);
            if (chunk <= 0)
            {
                std::cout << "Client disconnected or error receiving message\n";
                closesocket(clientSocket);
                delete handler;
                return;
            }
            totalBytesReceived += chunk;
        }

        // Step 3: Construct RequestInfo
        RequestInfo reqInfo;
        reqInfo.id = code;
        reqInfo.receivalTime = std::chrono::system_clock::now();        
        reqInfo.buffer = messageBuffer;

        // Step 4: Use appropriate handler (example here is login/sign-up)

        if (!handler->isRequestRelevant(reqInfo))
        {
            ErrorResponse err{ "Invalid request type" };
            auto errorMsg = JsonResponsePacketSerializer::serializeErrorResponse(err);
            send(clientSocket, reinterpret_cast<const char*>(errorMsg.data()), errorMsg.size(), 0);
            continue;
        }

        RequestResult result = handler->handleRequest(reqInfo);

        // Step 5: Send serialized response
        send(clientSocket, reinterpret_cast<const char*>(result.response.data()), result.response.size(), 0);

        if (result.newHandler != handler)
        {
            delete handler;
            handler = result.newHandler;
        }
    }

    delete handler;
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

Communicator::Communicator(RequestHandlerFactory& handlerFactory)
    :m_serverSocket(INVALID_SOCKET), m_handlerFactory(handlerFactory)
{

}
