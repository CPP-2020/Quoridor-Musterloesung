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
    virtual void drawGame(std::shared_ptr<const GameField> gameField) const = 0;
    virtual void showWinnerMessage(std::shared_ptr<const PlayerData> player) const = 0;
    virtual void showMessage(const std::string &message) const = 0;
    virtual int showMultipleChoice(const std::string &message,
                                   const std::vector<std::string> &answers) const = 0;
    virtual int showMultipleIntChoice(const std::string &message,
                                      int minValue,
                                      int maxValue) const = 0;
};

#endif // HACKATHON_UI_H
