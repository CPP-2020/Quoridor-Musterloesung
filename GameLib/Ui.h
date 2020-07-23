//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_UI_H
#define HACKATHON_UI_H

#include "GameField.h"
#include <memory>
#include <string>
#include <vector>

class Ui
{
  public:
    void drawGame(std::shared_ptr<const GameField> gameField) const;
    void showWinnerMessage(std::shared_ptr<const Player> player) const;
    void showMessage(const std::string &message) const;
    int showMultipleChoice(const std::string &message,
                           const std::vector<std::string> &answers) const;

  private:
    void clearScreen() const;
    void appendDelimiter(std::string &result,
                         std::shared_ptr<const GameField> gameField,
                         Coordinate const &coordinate) const;
    void appendContent(std::string &result,
                       std::shared_ptr<const GameField> gameField,
                       Coordinate const &coordinate) const;
};

#endif // HACKATHON_UI_H
