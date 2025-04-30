#pragma once
#include <string>
#include <list>
#include "LoggedUser.h"
#include "RoomData.h"

class Room
{
public:
    Room(RoomData metadata, LoggedUser creator);

    void addUser(LoggedUser user);
    void removeUser(const std::string& username);
    std::list<std::string> getAllUsers() const;
    RoomData getMetadata() const;
    bool isActive() const;

private:
    RoomData m_metadata;
    std::list<LoggedUser> m_users;
};
