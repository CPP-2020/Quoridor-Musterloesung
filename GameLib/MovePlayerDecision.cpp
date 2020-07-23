//
// Created by bened on 23.07.2020.
//

#include "MovePlayerDecision.h"
#include "Position.h"
#include "GameField.h"

MovePlayerDecision::MovePlayerDecision(Direction direction)
	: direction(direction)
{

}

bool MovePlayerDecision::isValidMove(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	return !isBorderInTheWay(player, gameField) &&
		   !isOutOfGameField(player, gameField);
}

void MovePlayerDecision::executeMove(std::shared_ptr<PlayerData> player, std::shared_ptr<GameField> gameField)
{
	if(isOtherPlayerInTheWay(player, gameField))
	{
		// We let the player "walk" two times in the same direction
		gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
		gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
	}
	else
	{
		gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
	}
}

std::shared_ptr<const Coordinate> MovePlayerDecision::getNextPlayerCoordinate(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	auto currentPlayerCoordinate = gameField->getPlayerPosition(player);
	std::shared_ptr<const Coordinate> nextPlayerCoordinate;
	switch (direction) {
		case Direction::Up:
			nextPlayerCoordinate = std::make_shared<const Coordinate>(currentPlayerCoordinate->getAboveCoordinate());
			break;
		case Direction::Down:
			nextPlayerCoordinate = std::make_shared<const Coordinate>(currentPlayerCoordinate->getBelowCoordinate());
			break;
		case Direction::Left:
			nextPlayerCoordinate = std::make_shared<const Coordinate>(currentPlayerCoordinate->getLeftCoordinate());
			break;
		case Direction::Right:
			nextPlayerCoordinate = std::make_shared<const Coordinate>(currentPlayerCoordinate->getRightCoordinate());
			break;
	}
	return nextPlayerCoordinate;
}

bool MovePlayerDecision::isBorderInTheWay(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	auto currentPlayerCoordinate = gameField->getPlayerPosition(player);
	return !gameField->noBorderBetweenCoordinates(*currentPlayerCoordinate, *getNextPlayerCoordinate(player, gameField));
}

bool MovePlayerDecision::isOutOfGameField(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	return !gameField->isValidCoordinate(*getNextPlayerCoordinate(player, gameField));
}

bool MovePlayerDecision::isOtherPlayerInTheWay(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	return gameField->isOtherPlayerAtPosition(player, *getNextPlayerCoordinate(player, gameField));
}
