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

Question Game::getQuestionForUser(const LoggedUser &user)
{
    auto &data = m_players[user];

    if (data.currentQuestion.getQuestion().empty())
    {
        if (m_questions.empty())
            throw std::exception("No more questions");

        data.currentQuestion = m_questions.back();
        m_questions.pop_back();
    }
    return data.currentQuestion;
}

bool Game::submitAnswer(const LoggedUser &user, unsigned int answerId, unsigned int answerTime)
{
    auto &data = m_players[user];

    bool isCorrect = (answerId == data.currentQuestion.getCorrectAnswerId());

    if (isCorrect)
        data.correctAnswerCount++;
    else
        data.wrongAnswerCount++;

    if (data.averageAnswerTime == 0)
        data.averageAnswerTime = answerTime;
    else
        data.averageAnswerTime = (data.averageAnswerTime + answerTime) / 2;

    data.currentQuestion = Question();

    return isCorrect;
}

void Game::removePlayer(const LoggedUser &user)
{
    submitGameStatsToDB(user);
    m_players.erase(user);
}

void Game::submitGameStatsToDB(const LoggedUser &user)
{
    auto &data = m_players[user];
    m_database->submitStatistics(user.getUsername(), data.correctAnswerCount, data.wrongAnswerCount,
                                 data.averageAnswerTime);
}


void Game::loadQuestions()
{
    std::list<Question> questionsFromDB = m_database->getQuestions(m_roomData.numOfQuestionsInGame);
    m_questions.assign(questionsFromDB.begin(), questionsFromDB.end());
}
