#include "LoggedUser.h"
#include "Room.h"

LoggedUser::LoggedUser(const std::string& username) : m_username(username), m_room(nullptr)
{
}

std::string LoggedUser::getUsername() const
{
    return m_username;
}

bool LoggedUser::operator<(const LoggedUser &other) const
{
    return this->m_username < other.m_username;
}

void LoggedUser::setRoom(Room &room)
{
    m_room = &room;
}

Room *LoggedUser::getRoom() const
{
    return m_room;
}

void LoggedUser::unsetRoom()
{
    m_room = nullptr;
}
