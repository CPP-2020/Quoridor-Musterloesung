//
// Created by bened on 23.07.2020.
//

#include "MovePlayerDecision.h"
#include "Position.h"
#include "GameField.h"
#include "../Graph/Graph.h"
#include "../Graph/Algorithm/BreadthFirstSearch.h"

MovePlayerDecision::MovePlayerDecision(Direction direction)
	: direction(direction)
{

}

bool MovePlayerDecision::isValidMove(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	return !isOutOfGameField(player, gameField) &&
		   !isBorderInTheWay(player, gameField) &&
		   !(isOtherPlayerInTheWay(player, gameField) && isPlayerInFrontSurroundedByBorders(player, gameField));
}

void MovePlayerDecision::executeMove(std::shared_ptr<PlayerData> player, std::shared_ptr<GameField> gameField)
{
	if(isOtherPlayerInTheWay(player, gameField))
	{
		// First go in the specified direction (to the position where the other player is)
		gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));

		if(!isOutOfGameField(player, gameField) && !isBorderInTheWay(player, gameField))
		{
			// Go into the same direction again
			gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
		}
		else
		{
			auto pos = *gameField->getPlayerPosition(player);
			auto reachableNeighbours = getReachableNeighbours(pos, gameField);
			for(int i = 0; i < reachableNeighbours.size(); i++)
			{
				if(reachableNeighbours.at(i) == getOppositeDirection(direction))
				{
					reachableNeighbours.erase(reachableNeighbours.begin() + i);
				}
			}
			direction = reachableNeighbours[0];
			gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
		}
	}
	else
	{
		gameField->setPlayerPosition(player, getNextPlayerCoordinate(player, gameField));
	}
}

Direction MovePlayerDecision::getOppositeDirection(const Direction &d) const
{
	switch (d) {
		case Direction::Down:
			return Direction::Up;
		case Direction::Up:
			return Direction::Down;
		case Direction::Left:
			return Direction::Right;
		case Direction::Right:
			return Direction::Left;
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

bool MovePlayerDecision::isPlayerInFrontSurroundedByBorders(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const
{
	return getReachableNeighbours(*getNextPlayerCoordinate(player, gameField), gameField).size() <= 1;
}

std::vector<Direction> MovePlayerDecision::getReachableNeighbours(const Coordinate &playerCoordinate, std::shared_ptr<const GameField> gameField) const
{
	std::vector<Direction> reachableNeighbours;

	Combinatorics::BreadthFirstSearch bfs(gameField->getGraph(),
										  gameField->getPosition(playerCoordinate).getVertex());


	if(gameField->isValidCoordinate(playerCoordinate.getLeftCoordinate()) &&
	   bfs.getPath(gameField->getPosition(playerCoordinate.getLeftCoordinate()).getVertex()).size() == 2)
	{
		reachableNeighbours.push_back(Direction::Left);
	}
	if(gameField->isValidCoordinate(playerCoordinate.getRightCoordinate()) &&
	   bfs.getPath(gameField->getPosition(playerCoordinate.getRightCoordinate()).getVertex()).size() == 2)
	{
		reachableNeighbours.push_back(Direction::Right);
	}
	if(gameField->isValidCoordinate(playerCoordinate.getAboveCoordinate()) &&
	   bfs.getPath(gameField->getPosition(playerCoordinate.getAboveCoordinate()).getVertex()).size() == 2)
	{
		reachableNeighbours.push_back(Direction::Up);
	}
	if(gameField->isValidCoordinate(playerCoordinate.getBelowCoordinate()) &&
	   bfs.getPath(gameField->getPosition(playerCoordinate.getBelowCoordinate()).getVertex()).size() == 2)
	{
		reachableNeighbours.push_back(Direction::Down);
	}

	return reachableNeighbours;
}
