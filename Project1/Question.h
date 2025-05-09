#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;
class Question
{

public:
	Question();
	Question(string question, vector<string> answers, unsigned int correctAnswer);

	string getQuestion();
	vector<string> getPossibleAnswers();
	unsigned int getCorrectAnswerId();

private:
	string m_question;
	vector<string> m_possibleAnswers;
	unsigned int m_correctAnswer;

};
