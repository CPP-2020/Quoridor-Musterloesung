//
// Created by bened on 23.07.2020.
//

#include "PlaceBorderDecision.h"
#include "Player.h"

PlaceBorderDecision::PlaceBorderDecision(const std::shared_ptr<const Player> player,
                                         const BorderOrientation &orientation,
                                         const Coordinate &topLeftCoordinate)
    : GameDecision(player)
    , topLeftCoordinate(topLeftCoordinate)
    , orientation(orientation)
{
}

bool PlaceBorderDecision::isValidMove(std::shared_ptr<const GameField> gameField) const
{
    if (player->getRemainingBorders() <= 0)
    {
        return false;
    }

    return false;
}

void PlaceBorderDecision::executeMove(std::shared_ptr<GameField> gameField)
{

}
