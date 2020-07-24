//
// Created by bened on 23.07.2020.
//


#ifndef HACKATHON_SMARTBOT_H
#define HACKATHON_SMARTBOT_H

#include "Player.h"


class SmartBot : public Player
{
  public:
    SmartBot(std::shared_ptr<PlayerData> playerData);
    std::shared_ptr<GameDecision> getGameDecision(std::shared_ptr<GameField const> gameField) override;
};

#endif // HACKATHON_SMARTBOT_H
