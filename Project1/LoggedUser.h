#pragma once
#include <string>
class Room;

class LoggedUser
{
public:
    explicit LoggedUser(const std::string& username);
    std::string getUsername() const;
    bool operator<(const LoggedUser &other) const;
    
    void setRoom(Room &room);
    Room *getRoom() const;
    void unsetRoom();
  private:
    std::string m_username;
    Room *m_room;
};
