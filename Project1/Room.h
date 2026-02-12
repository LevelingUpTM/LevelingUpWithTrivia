#pragma once
#include <string>
#include <list>
#include "LoggedUser.h"
#include "RoomData.h"
class Game;

class Room
{
public:
    Room(const RoomData& metadata, LoggedUser& creator);

    void addUser(LoggedUser& user);
    void removeUser(const std::string& username);
    const std::list<LoggedUser*>& getAllUsers() const;
    RoomData getMetadata() const;
    bool isActive() const;

    Game *getGame() const;
    void setGame(Game &game);
    void unsetGame();

private:
    RoomData m_metadata;
    std::list<LoggedUser*> m_users;
    Game *m_game;
};
