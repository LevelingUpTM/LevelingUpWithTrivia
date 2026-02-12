#pragma once

#include "Game.h"
#include "IDatabase.h"
#include "LoggedUser.h"
#include "Room.h"
#include <map>
#include <vector>

class GameManager
{
  public:
    GameManager(IDatabase *database);

    Game &createGame(Room& room);
    void deleteGame(unsigned int gameId);
    Game &getGame(unsigned int gameId);
    Game* getGameByUser(const LoggedUser &user);

  private:
    IDatabase *m_database;
    std::map<unsigned int, Game> m_games;
    std::map<std::string, unsigned int> m_usersToGames;
};
