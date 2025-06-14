#include "Room.h"

Room::Room(const RoomData& metadata, LoggedUser& creator) : m_metadata(metadata), m_game(nullptr)
{
    m_users.push_back(&creator);
}

void Room::addUser(LoggedUser& user)
{
    m_users.push_back(&user);
    user.setRoom(*this);
}

void Room::removeUser(const std::string& username)
{
    m_users.remove_if([&](const LoggedUser* u) {
        return u->getUsername() == username;
        });
}

const std::list<LoggedUser*>& Room::getAllUsers() const
{
    return m_users;
}

RoomData Room::getMetadata() const
{
    return m_metadata;
}

bool Room::isActive() const
{
    return m_metadata.isActive;
}

Game *Room::getGame() const
{
    return m_game;
}

void Room::setGame(Game &game)
{
    m_game = &game;
}

void Room::unsetGame()
{
    m_game = nullptr;
}
