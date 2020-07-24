//
// Created by bened on 24.07.2020.
//

#include "NoOutputUi.h"

void NoOutputUi::drawGame(std::shared_ptr<const GameField> gameField) const
{
}
void NoOutputUi::showWinnerMessage(std::shared_ptr<const PlayerData> player) const
{
}
void NoOutputUi::showMessage(const std::string &message) const
{
}
int NoOutputUi::showMultipleChoice(const std::string &message,
                                   const std::vector<std::string> &answers) const
{
    return 0;
}
int NoOutputUi::showMultipleIntChoice(const std::string &message,
                                      const int minValue,
                                      const int maxValue) const
{
    return 0;
}
