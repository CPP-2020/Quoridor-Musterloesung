//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMERULES_H
#define HACKATHON_GAMERULES_H


#include "PlayerId.h"
#include "GameField.h"

class GameRules {
public:
    void didPlayerWin(const PlayerId& playerId, const GameField& gameField);
};


#endif //HACKATHON_GAMERULES_H
