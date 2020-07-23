//
// Created by bened on 23.07.2020.
//

#include "MovePlayerDecision.h"

MovePlayerDecision::MovePlayerDecision(Direction direction)
	: direction(direction)
{

}

bool MovePlayerDecision::isValidMove(std::shared_ptr<const Player> player, std::shared_ptr<const GameField> gameField) const
{
	return !isBorderInTheWay(gameField) &&
		   !isOutOfGameField(gameField) &&
		   !isOtherPlayerInTheWay(gameField);
}

void MovePlayerDecision::executeMove(std::shared_ptr<Player> player, std::shared_ptr<GameField> gameField)
{

}

bool MovePlayerDecision::isBorderInTheWay(std::shared_ptr<const GameField> gameField) const
{
	// What the current player is --> ?
	// x Where the player currently is (coordinates), --> Public GameField method
	// Where the next coordinate in the specified direction is --> Public coordinate method
	// x Wether there is an edge between these coordinates --> Private GameField method
	//gameField->getPlayerPosition(player)
    return false;
}

bool MovePlayerDecision::isOutOfGameField(std::shared_ptr<const GameField> gameField) const
{

    return false;
}

bool MovePlayerDecision::isOtherPlayerInTheWay(std::shared_ptr<const GameField> gameField) const
{
    return false;
}
