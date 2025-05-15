#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class Question
{
  public:
    Question();
    Question(int id, string question, vector<string> answers, unsigned int correctAnswer, string difficulty, string category);

    int getId() const;
    string getQuestion() const;
    vector<string> getPossibleAnswers() const;
    unsigned int getCorrectAnswerId() const;
    string getDifficulty() const;
    string getCategory() const;

  private:
    int m_id;                         
    string m_question;                
    vector<string> m_possibleAnswers; 
    unsigned int m_correctAnswer;     
    string m_difficulty;              
    string m_category;                
};
