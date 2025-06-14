#include "GameManager.h"
#include "Game.h"


GameManager::GameManager(IDatabase* database)
    : m_database(database)
{
}

Game& GameManager::createGame(Room& room)
{
    return m_games.emplace(
        std::piecewise_construct, 
        std::forward_as_tuple(room.getMetadata().id),
        std::forward_as_tuple(room, m_database)
    ).first->second;
}

void GameManager::deleteGame(unsigned int gameId)
{
    m_games.at(gameId).getRoom().unsetGame();
    m_games.erase(gameId);
}

Game &GameManager::getGame(unsigned int gameId)
{
    return m_games.at(gameId);
}

Game* GameManager::getGameByUser(const LoggedUser &user)
{
    if (user.getRoom() == nullptr)
        return nullptr;
    if (user.getRoom()->getGame() == nullptr)
        return nullptr;

    return user.getRoom()->getGame();
}