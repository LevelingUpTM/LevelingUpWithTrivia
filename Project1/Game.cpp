#include "Game.h"

Game::Game(Room room, IDatabase *database)
    : m_database(database), m_gameId(room.getMetadata().id), m_roomData(room.getMetadata())
{
    // Initialize players
    for (const auto &username : room.getAllUsers())
    {
        LoggedUser user(username);
        m_players[user] = GameData();
    }
    loadQuestions();
}

unsigned int Game::getGameId() const
{
    return m_gameId;
}

void Game::loadQuestions()
{
    std::list<Question> questionsFromDB = m_database->getQuestions(m_roomData.numOfQuestionsInGame);
    m_questions.assign(questionsFromDB.begin(), questionsFromDB.end());
}
