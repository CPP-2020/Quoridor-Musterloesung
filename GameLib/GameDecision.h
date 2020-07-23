//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMEDECISION_H
#define HACKATHON_GAMEDECISION_H

#include "GameField.h"
#include "PlayerData.h"
#include <memory>

class Player;

class GameDecision {
public:
    virtual bool isValidMove(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField) const = 0;
    virtual void executeMove(std::shared_ptr<PlayerData> player, std::shared_ptr<GameField> gameField) = 0;
};

#endif //HACKATHON_GAMEDECISION_H
