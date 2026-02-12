#pragma once
#include <map>
#include "Room.h"
#include <vector>

class RoomManager
{
public:
    Room& createRoom(LoggedUser& creator, RoomData metadata);
    void deleteRoom(unsigned int roomId);
    Room& getRoom(unsigned int roomId);
    std::vector<RoomData> getRooms() const;
    bool getRoomState(unsigned int roomId) const; // true = active
    unsigned int getNextRoomId();

private:
    std::map<unsigned int, Room> m_rooms;
    unsigned int m_nextRoomId = 1;
};
