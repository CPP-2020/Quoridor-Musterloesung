//
// Created by bened on 23.07.2020.
//

#include "RandomBot.h"
#include <ctime> 
#include "Coordinate.h"
#include "MovePlayerDecision.h"
#include "PlaceBorderDecision.h"


std::shared_ptr<GameDecision> RandomBot::getGameDecision(std::shared_ptr<GameField const> gameField)
{
    srand((unsigned)time(0));

    
    int i = (rand() % 2) ;
    if (i == 0)
    {
        while (true)
        {
            Direction moveDirection = (Direction)(rand() % 4);
            auto moveDecision = std::make_shared<MovePlayerDecision>(moveDirection);
            if (moveDecision->isValidMove(shared_from_this(), gameField))
            {
                return moveDecision;
            }
        }

    }
    else
    {
        BorderOrientation borderOrientation;

        Coordinate *coordinate;

        if ((rand() % 2)==1)
        {
            borderOrientation = BorderOrientation::Vertical;
        }
        else
        {
            borderOrientation = BorderOrientation::Horizontal;
        }
        coordinate = new Coordinate((rand() % 9), (rand() % 9));

        if (gameField->isValidCoordinate(*coordinate))
        {
            auto borderDesicion = std::make_shared<PlaceBorderDecision>(borderOrientation, *coordinate);
            return borderDesicion;
        }

    }

}
RandomBot::RandomBot(const std::string &name, const int &id, const BoardSides &startSide)
        : Player(name, id, startSide)
{
}
