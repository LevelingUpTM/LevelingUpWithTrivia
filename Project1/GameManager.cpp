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
    Game &createdGame = m_games.back();
    unsigned int gameId = createdGame.getGameId();

    for (const std::string& userName : room.getAllUsers())
    {
        m_usersToGames[userName] = gameId;
    }

    return createdGame;
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

Game &GameManager::getGameByUser(const LoggedUser &user)
{
    std::string username = user.getUsername();
    if (m_usersToGames.find(username) == m_usersToGames.end())
    {
        throw std::exception("User not in any game");
    }

    unsigned int gameId = m_usersToGames[username];
    return getGame(gameId);
}