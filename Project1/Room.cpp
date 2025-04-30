#include "Room.h"

Room::Room(RoomData metadata, LoggedUser creator)
    : m_metadata(metadata)
{
    m_users.push_back(creator);
}

void Room::addUser(LoggedUser user)
{
    m_users.push_back(user);
}

void Room::removeUser(const std::string& username)
{
    m_users.remove_if([&](const LoggedUser& u) {
        return u.getUsername() == username;
        });
}

std::list<std::string> Room::getAllUsers() const
{
    std::list<std::string> names;
    for (const auto& user : m_users)
        names.push_back(user.getUsername());
    return names;
}

RoomData Room::getMetadata() const
{
    return m_metadata;
}

bool Room::isActive() const
{
    return m_metadata.isActive;
}
