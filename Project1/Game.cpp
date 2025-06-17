#include "Game.h"
#include "JsonResponsePacketSerializer.h"
Game::Game(Room& room, IDatabase *database)
    : m_database(database), m_gameId(room.getMetadata().id), m_roomData(room.getMetadata()), m_room(room)
{
    // Initialize players
    for (const LoggedUser* user : room.getAllUsers())
    {
        m_players.emplace(user, GameData());
    }
    loadQuestions();
}

unsigned int Game::getGameId() const
{
    return m_gameId;
}

Question* Game::getQuestionForUser(const LoggedUser &user)
{
    GameData &data = m_players.at(&user);

    if (m_questions.size() <= data.currentQuestion)
        return nullptr;

    Question &currentQuestion = m_questions.at(data.currentQuestion++);
    
    return &currentQuestion;
}

bool Game::submitAnswer(const LoggedUser &user, unsigned int answerId, unsigned int answerTime)
{
    GameData& data = m_players.at(&user);
    Question *question = getQuestionForUser(user);
    if (question == nullptr)
    {
        throw std::exception("got to last question");
    }
    bool isCorrect = (answerId == question->getCorrectAnswerId());

    if (isCorrect)
        data.correctAnswerCount++;
    else
        data.wrongAnswerCount++;

    if (data.averageAnswerTime == 0)
        data.averageAnswerTime = answerTime;
    else
        data.averageAnswerTime = (data.averageAnswerTime + answerTime) / 2;

    return isCorrect;
}

void Game::removePlayer(const LoggedUser &user)
{
    submitGameStatsToDB(user);
    m_players.erase(&user);
}

std::vector<PlayerResults> Game::getPlayersResults() const
{
    std::vector<PlayerResults> results;

    for (const auto &pair : m_players)
    {
        PlayerResults res;
        res.username = pair.first->getUsername();
        res.correctAnswerCount = pair.second.correctAnswerCount;
        res.wrongAnswerCount = pair.second.wrongAnswerCount;
        res.averageAnswerTime = pair.second.averageAnswerTime;
        results.push_back(res);
    }

    return results;
}

Room &Game::getRoom() const
{
    return m_room;
}

void Game::submitGameStatsToDB(const LoggedUser &user)
{
    GameData &data = m_players.at(&user);
    m_database->submitStatistics(user.getUsername(), data.correctAnswerCount, data.wrongAnswerCount,
                                 data.averageAnswerTime);
}


void Game::loadQuestions()
{
    std::list<Question> questionsFromDB = m_database->getQuestions(m_roomData.numOfQuestionsInGame);
    m_questions.assign(questionsFromDB.begin(), questionsFromDB.end());
}
