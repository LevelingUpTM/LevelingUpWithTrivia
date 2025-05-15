#include "Question.h"

Question::Question() : m_id(0), m_question(""), m_correctAnswer(1), m_difficulty(""), m_category("")
{
    m_possibleAnswers = {"", "", "", ""};
}

Question::Question(int id, string question, vector<string> answers, unsigned int correctAnswer, string difficulty,
                   string category)
    : m_id(id), m_question(question), m_possibleAnswers(answers), m_correctAnswer(correctAnswer),
      m_difficulty(difficulty), m_category(category)
{
}

int Question::getId() const
{
    return m_id;
}

string Question::getQuestion() const
{
    return m_question;
}

vector<string> Question::getPossibleAnswers() const
{
    return m_possibleAnswers;
}

unsigned int Question::getCorrectAnswerId() const
{
    return m_correctAnswer;
}

string Question::getDifficulty() const
{
    return m_difficulty;
}

string Question::getCategory() const
{
    return m_category;
}
