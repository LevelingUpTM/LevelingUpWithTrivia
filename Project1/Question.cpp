#include "Question.h"

Question::Question()
{
}

Question::Question(string question, vector<string> answers, unsigned int correctAnswer)
{
	this->m_question = question;
	this->m_possibleAnswers = answers;
	this->correctAnswer = correctAnswer;
}

string Question::getQuestion()
{
	return this->m_question;
}

vector<string> Question::getPossibleAnswers()
{
	return this->m_possibleAnswers;
}

unsigned int Question::getCorrectAnswerId()
{
	return this->m_correctAnswer;
}