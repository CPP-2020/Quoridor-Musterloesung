//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMEDECISION_H
#define HACKATHON_GAMEDECISION_H


#include "GameField.h"

class GameDecision {
public:
    virtual bool isValidMove(const GameField& gameField) = 0;
    virtual void executeMove(GameField& gameField) = 0;
};


#endif //HACKATHON_GAMEDECISION_H
