//
// Created by bened on 24.07.2020.
//

#ifndef HACKATHON_NOOUTPUTUI_H
#define HACKATHON_NOOUTPUTUI_H

#include "Ui.h"

class NoOutputUi : public Ui
{
  public:
    void drawGame(std::shared_ptr<const GameField> gameField) const override;
    void showWinnerMessage(std::shared_ptr<const PlayerData> player) const override;
    void showMessage(const std::string &message) const override;
    int showMultipleChoice(const std::string &message,
                           const std::vector<std::string> &answers) const override;
    int showMultipleIntChoice(const std::string &message,
                              const int minValue,
                              const int maxValue) const override;
};

#endif // HACKATHON_NOOUTPUTUI_H
