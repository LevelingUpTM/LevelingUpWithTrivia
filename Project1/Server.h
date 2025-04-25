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
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;

public:
	void run();
};
