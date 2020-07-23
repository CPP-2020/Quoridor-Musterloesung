//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_MOVEPLAYERDECISION_H
#define HACKATHON_MOVEPLAYERDECISION_H

#include "GameDecision.h"

enum Direction {
    Up,
    Down,
    Left,
    Right,
};

class MovePlayerDecision : public GameDecision {
public:
	MovePlayerDecision(std::shared_ptr<const Player> player, Direction direction);

	bool isValidMove(std::shared_ptr<const GameField> gameField) const override;
	void executeMove(std::shared_ptr<const GameField> gameField) override;

private:
	Direction direction;
	// Keine Mauer, Spielfeld nicht zu Ende, anderer Spieler
	bool isBorderInTheWay(std::shared_ptr<const GameField> gameField) const;
	bool isOutOfGameField(std::shared_ptr<const GameField> gameField) const;
	bool isOtherPlayerInTheWay(std::shared_ptr<const GameField> gameField) const;
};


#endif //HACKATHON_MOVEPLAYERDECISION_H
