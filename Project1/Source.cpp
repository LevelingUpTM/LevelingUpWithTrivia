#include "Server.h"
#include <iostream>

int main()
{
    try
    {
        // Create the server
        Server server;

        // Run the server
        server.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
