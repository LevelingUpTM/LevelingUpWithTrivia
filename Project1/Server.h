#pragma once
#include "Communicator.h"
#include "IDataBase.h"
#include "RequestHandlerFactory.h"
#include <string>
#include <iostream>
#include <thread>
class Server
{
private:
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
	Communicator m_communicator;

public:
	void run();
	Server();
	~Server();
};
