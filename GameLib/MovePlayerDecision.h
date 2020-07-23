//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_MOVEPLAYERDECISION_H
#define HACKATHON_MOVEPLAYERDECISION_H

#include "GameDecision.h"
#include "PlayerData.h"

enum Direction {
    Up,
    Down,
    Left,
    Right,
};

class MovePlayerDecision : public GameDecision {
public:
	MovePlayerDecision(Direction direction);

	bool isValidMove(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const override;
	void executeMove(std::shared_ptr<PlayerData> player, std::shared_ptr<GameField> gameField) override;

private:
	Direction direction;
	std::shared_ptr<const Coordinate> getNextPlayerCoordinate(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const;
	bool isBorderInTheWay(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const;
	bool isOutOfGameField(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const;
	bool isOtherPlayerInTheWay(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const;
};


#endif //HACKATHON_MOVEPLAYERDECISION_H
