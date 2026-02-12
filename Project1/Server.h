#pragma once
#include "Communicator.h"
#include "IDataBase.h"
#include "RequestHandlerFactory.h"
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
