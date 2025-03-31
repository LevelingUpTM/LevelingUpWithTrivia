#include "Server.h"

void Server::run()
{
	std::thread t(&Communicator::startHandleRequest, &m_communicator);
	std::string input;
	while (true)
	{
		std::cout << "Enter command: ";
		std::cin >> input;
		if (input == "EXIT") 
		{
			std::cout << "Shutting down server...\n";
			break;
		}
	}
	t.join();
}
