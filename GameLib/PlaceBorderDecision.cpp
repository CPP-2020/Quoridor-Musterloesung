//
// Created by bened on 23.07.2020.
//

#include "PlaceBorderDecision.h"
#include "Player.h"
#include <assert.h>

PlaceBorderDecision::PlaceBorderDecision(const BorderOrientation &orientation,
                                         const Coordinate &topLeftCoordinate)
        : topLeftCoordinate(topLeftCoordinate)
        , orientation(orientation)
{
}

bool PlaceBorderDecision::isValidMove(std::shared_ptr<const Player> player,
                                      std::shared_ptr<const GameField> gameField) const
{
    if (player->getRemainingBorders() <= 0)
    {
        return false;
    }

    auto topRightCoordinate = topLeftCoordinate.getRightCoordinate();
    auto bottomLeftCoordinate = topLeftCoordinate.getBelowCoordinate();
    auto bottomRightCoordinate = bottomLeftCoordinate.getRightCoordinate();

    if (orientation == BorderOrientation::Horizontal)
    {
        return gameField->noBorderBetweenCoordinates(topLeftCoordinate, bottomLeftCoordinate) &&
            gameField->noBorderBetweenCoordinates(topRightCoordinate, bottomRightCoordinate);
    }

    if (orientation == BorderOrientation::Vertical)
    {
        return gameField->noBorderBetweenCoordinates(topLeftCoordinate, topRightCoordinate) &&
            gameField->noBorderBetweenCoordinates(bottomLeftCoordinate, bottomRightCoordinate);
    }

    return false;
}

void PlaceBorderDecision::executeMove(std::shared_ptr<Player> player,
                                      std::shared_ptr<GameField> gameField)
{
    assert(isValidMove(player, gameField));

    auto topRightCoordinate = topLeftCoordinate.getRightCoordinate();
    auto bottomLeftCoordinate = topLeftCoordinate.getBelowCoordinate();
    auto bottomRightCoordinate = bottomLeftCoordinate.getRightCoordinate();

    if (orientation == BorderOrientation::Horizontal)
    {
        gameField->setBorderBetweenCoordinates(topLeftCoordinate, bottomLeftCoordinate);
        gameField->setBorderBetweenCoordinates(topRightCoordinate, bottomRightCoordinate);
    }

    if (orientation == BorderOrientation::Vertical)
    {
        gameField->setBorderBetweenCoordinates(topLeftCoordinate, topRightCoordinate);
        gameField->setBorderBetweenCoordinates(bottomLeftCoordinate, bottomRightCoordinate);
    }

    player->setRemainingBorders(player->getRemainingBorders() - 1);
}
