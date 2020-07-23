//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_UI_H
#define HACKATHON_UI_H

#include <memory>
#include <vector>
#include <string>

class Player;
class GameField;
class Coordinate;

class Ui {
public:
	void drawGame(std::shared_ptr<const GameField> gameField) const;
	void showWinnerMessage(std::shared_ptr<const Player> player) const;
	int	 showMultipleChoice(const std::string& message, const std::vector<std::string>& answers) const;

private:
	void clearScreen() const;
	void appendDelimiter(std::string & result, std::shared_ptr<const GameField> gameField, Coordinate const & coordinate) const;
	void appendContent(std::string & result, std::shared_ptr<const GameField> gameField, Coordinate const & coordinate) const;
};


#endif //HACKATHON_UI_H
