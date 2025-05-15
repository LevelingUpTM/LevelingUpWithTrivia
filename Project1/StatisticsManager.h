#pragma once

#include "IDatabase.h"
#include <string>
#include <vector>

class StatisticsManager
{
  public:
    explicit StatisticsManager(IDatabase *db);

    // Returns top player scores
    std::vector<std::string> getHighScore();

    // Returns statistics for the username
    std::vector<std::string> getUserStatistics(const std::string &username);

  private:
    IDatabase *m_database;

};
