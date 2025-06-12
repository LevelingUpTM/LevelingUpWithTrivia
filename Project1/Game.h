#pragma once

#include <vector>
#include <map>
#include "Question.h"
#include "Room.h"
#include "LoggedUser.h"
#include "IDatabase.h"
#include "JsonResponsePacketSerializer.h"

struct GameData
{
    Question currentQuestion;
    unsigned int correctAnswerCount = 0;
    unsigned int wrongAnswerCount = 0;
    unsigned int averageAnswerTime = 0;
};


class Game
{
  public:
    Game(Room room, IDatabase *database);
    unsigned int getGameId() const;
    Question getQuestionForUser(const LoggedUser &user);
    bool submitAnswer(const LoggedUser &user, unsigned int answerId, unsigned int answerTime);
    void removePlayer(const LoggedUser &user);
    std::vector<PlayerResults> getPlayersResults() const;

  private:
    void loadQuestions();
    void submitGameStatsToDB(const LoggedUser &user);
    std::vector<Question> m_questions;
    std::map<LoggedUser, GameData> m_players;
    unsigned int m_gameId;
    IDatabase* m_database;
    RoomData m_roomData;
};