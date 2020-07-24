//
// Created by bened on 23.07.2020.
//

#include "SmartBot.h"
#include "Coordinate.h"
#include "MovePlayerDecision.h"
#include "PlaceBorderDecision.h"
#include "../Graph/Algorithm/BreadthFirstSearch.h"


SmartBot::SmartBot(std::shared_ptr<PlayerData> playerData)
    : Player(playerData)
{
}

std::shared_ptr<GameDecision> SmartBot::getGameDecision(std::shared_ptr<GameField const> gameField) const
{
    
        while (true)
        {
            const Combinatorics::Graph &gameGraph = gameField->getGraph();
            
            auto &playerPosition =gameField->getPosition(*gameField->getPlayerPosition(playerData)).getVertex();           
            Combinatorics::BreadthFirstSearch search(gameGraph, playerPosition);
            auto startSide = playerData->getStartSide();
            int x = 0;
            if (startSide == BoardSides::Left)
            {
                x = gameField->getWidth() - 1;
            }
            
            auto way = search.getPath(gameField->getPosition({x, gameField->getHeight() / 2}).getVertex());
            int nodex;
            int nodey;
            for (int y = 0; y <gameField->getHeight() ;y++)
            {
                for (int x = 0; x < gameField->getWidth(); x++)
                {
                    auto &position = gameField->getPosition({x, y}).getVertex();
                    if (*(++way.begin()) == position.getId())
                    {
                        nodex = x;
                        nodey = y;
                    }           
                }
            }
            
            Direction direction;
            int playerx = gameField->getPlayerPosition(playerData)->x();
            int playery = gameField->getPlayerPosition(playerData)->y();

            if (nodex > playerx)
            {
                direction = Direction::Right ;
            }
            if (nodex < playerx)
            {
                direction = Direction::Left;
            }
            if (nodey > playery)
            {
                direction = Direction::Down;
            }
            if (nodey < playery)
            {
                direction = Direction::Up;
            }
            auto moveDecision = std::make_shared<MovePlayerDecision>(direction);
            if (moveDecision->isValidMove(playerData, gameField))
            {
                return moveDecision;
            }

        }
        
}
