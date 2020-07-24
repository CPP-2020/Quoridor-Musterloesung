//
// Created by bened on 23.07.2020.
//

#include "RandomBot.h"
#include <ctime> 
#include "Coordinate.h"
#include "MovePlayerDecision.h"
#include "PlaceBorderDecision.h"


RandomBot::RandomBot(std::shared_ptr<PlayerData> playerData)
    : Player(playerData)
{
}

std::shared_ptr<GameDecision> RandomBot::getGameDecision(std::shared_ptr<GameField const> gameField) const
{
    srand((unsigned)time(0));

    
    if ((0 == rand() % 2) && (0 != playerData->getRemainingBorders()))
    {
        BorderOrientation borderOrientation;

        Coordinate *coordinate;

        if ((rand() % 2) == 1)
        {
            borderOrientation = BorderOrientation::Vertical;
        }
        else
        {
            borderOrientation = BorderOrientation::Horizontal;
        }
        coordinate = new Coordinate((rand() % (gameField->getWidth() - 2)),
                                    (rand() % (gameField->getHeight() - 2)));

        if (gameField->isValidCoordinate(*coordinate))
        {
            auto borderDesicion =
                std::make_shared<PlaceBorderDecision>(borderOrientation, *coordinate);
            return borderDesicion;
        }
    }
    else
    {
        while (true)
        {
            Direction moveDirection = (Direction)(rand() % 4);
            auto moveDecision = std::make_shared<MovePlayerDecision>(moveDirection);
            if (moveDecision->isValidMove(playerData, gameField))
            {
                return moveDecision;
            }
        }
    }
    
}
