cmake_minimum_required(VERSION 3.31)
project(Project1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project1
        Communicator.cpp
        Communicator.h
        IDataBase.h
        IRequestHandler.h
        json.hpp
        JsonRequestPacketDeserializer.cpp
        JsonRequestPacketDeserializer.h
        JsonResponsePacketSerializer.cpp
        JsonResponsePacketSerializer.h
        LoggedUser.cpp
        LoggedUser.h
        LoginManager.cpp
        LoginManager.h
        LoginRequestHandler.cpp
        LoginRequestHandler.h
        RequestHandlerFactory.cpp
        RequestHandlerFactory.h
        RequestInfo.h
        RequestResult.h
        Room.cpp
        Room.h
        RoomData.h
        RoomManager.cpp
        RoomManager.h
        Server.cpp
        Server.h
        Source.cpp
        sqlite3.c
        sqlite3.h
        SqliteDatabase.cpp
        SqliteDatabase.h)
target_link_libraries(Project1 PRIVATE Ws2_32)
