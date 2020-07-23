//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_MOVEPLAYERDECISION_H
#define HACKATHON_MOVEPLAYERDECISION_H

#include "GameDecision.h"

enum Direction {
    Up,
    Down,
    Left,
    Right,
};

class MovePlayerDecision : public GameDecision {
public:
    MovePlayerDecision(Direction direction);

    bool isValidMove(const GameField &gameField) override;
    void executeMove(GameField &gameField) override;
};


#endif //HACKATHON_MOVEPLAYERDECISION_H
