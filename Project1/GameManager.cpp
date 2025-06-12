#include "GameManager.h"
#include "Game.h"


GameManager::GameManager(IDatabase* database)
    : m_database(database)
{
}

Game& GameManager::createGame(Room room)
{
    Game newGame(room, m_database);
    m_games.push_back(newGame);
    return m_games.back();
}

void GameManager::deleteGame(unsigned int gameId)
{
    auto it = std::remove_if(m_games.begin(), m_games.end(),
        [gameId](const Game& game) { return game.getGameId() == gameId; });

    if (it != m_games.end())
        m_games.erase(it, m_games.end());
}

Game& GameManager::getGame(unsigned int gameId)
{
    for (auto& game : m_games)
    {
        if (game.getGameId() == gameId)
            return game;
    }
    throw std::exception("Game not found");
}
