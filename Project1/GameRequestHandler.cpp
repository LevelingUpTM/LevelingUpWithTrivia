#include "GameRequestHandler.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "MenuRequestHandler.h"
#include "StatusCodes.h"

GameRequestHandler::GameRequestHandler(Game &game, LoggedUser& user, GameManager &gameManager,
                                       RequestHandlerFactory &handlerFactory)
    : m_game(game), m_user(user), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

bool GameRequestHandler::isRequestRelevant(RequestInfo &request)
{
    return request.id == GET_QUESTION_REQUEST || request.id == SUBMIT_ANSWER_REQUEST ||
           request.id == GET_GAME_RESULTS_REQUEST || request.id == LEAVE_GAME_REQUEST;
}

RequestResult GameRequestHandler::handleRequest(RequestInfo &request)
{
    switch (request.id)
    {
    case GET_QUESTION_REQUEST:
        return getQuestion(request);
    case SUBMIT_ANSWER_REQUEST:
        return submitAnswer(request);
    case GET_GAME_RESULTS_REQUEST:
        return getGameResults(request);
    case LEAVE_GAME_REQUEST:
        return leaveGame(request);
    default:
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Invalid request for game."}), nullptr};
    }
}

RequestResult GameRequestHandler::getQuestion(RequestInfo request)
{
    try
    {
        Question* question = m_game.getQuestionForUser(m_user);
        if (question == nullptr)
        {
            RequestResult rr;
            rr.response = JsonResponsePacketSerializer::serializeErrorResponse({"end of questions"});
            rr.newHandler = this;
            return rr;
        }
        GetQuestionResponse response;
        response.status = SUCCESS;
        response.question = question->getQuestion();
        std::vector<std::string> answersVec = question->getPossibleAnswers();
        for (unsigned int i = 0; i < answersVec.size(); ++i)
        {
            response.answers[i] = answersVec[i];
        }
        return {JsonResponsePacketSerializer::serializeGetQuestionResponse(response), this};
    }
    catch (...)
    {
        return {JsonResponsePacketSerializer::serializeErrorResponse({"Failed to get question."}), this};
    }
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo request)
{
    SubmitAnswerRequest data = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(request.buffer);

    bool isCorrect = m_game.submitAnswer(m_user, data.answerId, data.answerTime);
    SubmitAnswerResponse response;
    response.status = SUCCESS;
    response.correctAnswerId = isCorrect ? data.answerId : -1;

    return {JsonResponsePacketSerializer::serializeSubmitAnswerResponse(response), this};
}

RequestResult GameRequestHandler::getGameResults(RequestInfo request)
{
    GetGameResultsResponse response;
    response.status = SUCCESS;
    const auto &playersStats = m_game.getPlayersResults();
    response.result = playersStats;

    return {JsonResponsePacketSerializer::serializeGetGameResultsResponse(response), this};
}

RequestResult GameRequestHandler::leaveGame(RequestInfo request)
{
    m_game.removePlayer(m_user);
    m_gameManager.deleteGame(m_game.getGameId());

    LeaveGameResponse response;
    response.status = SUCCESS;

    return {JsonResponsePacketSerializer::serializeLeaveGameResponse(response),
            m_handlerFactory.createMenuRequestHandler(m_user)};
}