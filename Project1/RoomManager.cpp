#include "RoomManager.h"

Room RoomManager::createRoom(const LoggedUser& creator, RoomData metadata)
{
    metadata.id = m_nextRoomId++;
    metadata.isActive = false;
    Room room(metadata, creator);
    m_rooms.insert({metadata.id, room});
    return room;
}

void RoomManager::deleteRoom(const unsigned int roomId)
{
    m_rooms.erase(roomId);
}

Room RoomManager::getRoom(const unsigned int roomId)
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

bool RoomManager::getRoomState(const unsigned int roomId) const
{
    return m_rooms.at(roomId).isActive();
}
