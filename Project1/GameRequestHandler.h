#pragma once
#include "Game.h"
#include "LoggedUser.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "RequestResult.h"
#include "RequestInfo.h"

class GameRequestHandler : public IRequestHandler
{
  public:
    GameRequestHandler(Game &game, LoggedUser user, GameManager &gameManager, RequestHandlerFactory &handlerFactory);
    bool isRequestRelevant(RequestInfo &request) override;
    RequestResult handleRequest(RequestInfo &request) override;
  private:
    Game &m_game;
    LoggedUser m_user;
    GameManager &m_gameManager;
    RequestHandlerFactory &m_handlerFactory;

    RequestResult getQuestion(RequestInfo request);
    RequestResult submitAnswer(RequestInfo request);
    RequestResult getGameResults(RequestInfo request);
    RequestResult leaveGame(RequestInfo request);
};
