//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_UI_H
#define HACKATHON_UI_H

#include "GameField.h"
#include "PlayerId.h"

class Ui {
public:
	void drawGame(const GameField& gameField) const;
  void showWinnerMessage(const PlayerId& playerId) const;
	int	 showMultipleChoice(const std::string& message, const std::vector<std::string>& answers) const;

private:
  void clearScreen() const;
  void appendDelimiter(std::string & result, const GameField &gameField, Coordinate const & coordinate) const;
	void appendContent(std::string & result, const GameField &gameField, Coordinate const & coordinate) const;
};


#endif //HACKATHON_UI_H
