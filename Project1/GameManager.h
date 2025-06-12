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

    Game &createGame(Room room);
    void deleteGame(unsigned int gameId);
    Game &getGame(unsigned int gameId);

  private:
    IDatabase *m_database;
    std::vector<Game> m_games;
};
