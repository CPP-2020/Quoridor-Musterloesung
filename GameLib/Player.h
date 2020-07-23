//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLAYER_H
#define HACKATHON_PLAYER_H


#include <string>
#include "GameDecision.h"
#include "GameField.h"
#include "PlayerId.h"
#include <memory>

class Player {
public:
    Player(std::shared_ptr<PlayerId> &newPlayerData);
    virtual std::string getPlayerName() = 0;
    virtual GameDecision getGameDecision(const GameField& gameField) = 0;

    std::shared_ptr<PlayerId> playerData;
};


#endif //HACKATHON_PLAYER_H
