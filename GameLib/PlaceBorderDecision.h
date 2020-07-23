//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLACEBORDERDECISION_H
#define HACKATHON_PLACEBORDERDECISION_H


#include "GameDecision.h"

class PlaceBorderDecision : public GameDecision {
public:
    bool isValidMove(const GameField &gameField) override;
    void executeMove(GameField &gameField) override;
};


#endif //HACKATHON_PLACEBORDERDECISION_H
