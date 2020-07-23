//
// Created by bened on 23.07.2020.
//

#include "GameRules.h"
#include "GameField.h"
#include "Player.h"


bool GameRules::didPlayerWin(std::shared_ptr<const Player> player, std::shared_ptr<const GameField> gameField)
{
    auto startSide = player->getStartSide();

    int columnToCheck = -1;

    if(startSide == BoardSides::Left){
        columnToCheck = gameField->getWidth() - 1;
    }
    else if (startSide == BoardSides::Right) {
        columnToCheck = 0;
    }

    return gameField->getPlayerPosition(player)->x() == columnToCheck;
}
