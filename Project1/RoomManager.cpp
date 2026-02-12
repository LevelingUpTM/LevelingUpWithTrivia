#include "RoomManager.h"

Room& RoomManager::createRoom(LoggedUser& creator, RoomData metadata)
{
    metadata.id = getNextRoomId();
    metadata.isActive = false;
    Room& room = m_rooms.emplace(
        std::piecewise_construct,
        std::forward_as_tuple(metadata.id),
        std::forward_as_tuple(metadata, creator)
    ).first->second;
    creator.setRoom(room);
    return room;
}

void RoomManager::deleteRoom(const unsigned int roomId)
{
    const std::list<LoggedUser *> &users = m_rooms.at(roomId).getAllUsers();
    for (LoggedUser* user : users)
    {
        user->unsetRoom();
    }
    m_rooms.erase(roomId);
}

Room& RoomManager::getRoom(const unsigned int roomId)
{
    return m_rooms.at(roomId);
}

std::vector<RoomData> RoomManager::getRooms() const
{
    std::vector<RoomData> list;
    for (const auto& pair : m_rooms)
    {
        list.push_back(pair.second.getMetadata());
    }
    return list;
}

unsigned int RoomManager::getNextRoomId()
{
    return m_nextRoomId++;
}

bool RoomManager::getRoomState(const unsigned int roomId) const
{
    return m_rooms.at(roomId).isActive();
}
