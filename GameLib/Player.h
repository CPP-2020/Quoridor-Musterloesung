//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLAYER_H
#define HACKATHON_PLAYER_H


#include <string>
#include "GameDecision.h"
#include "GameField.h"

class Player {
public:
    virtual std::string getPlayerName() = 0;
    virtual GameDecision getGameDecision(const GameField& gameField) = 0;
};


#endif //HACKATHON_PLAYER_H
