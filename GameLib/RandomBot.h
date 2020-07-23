//
// Created by bened on 23.07.2020.
//


#ifndef HACKATHON_RANDOMBOT_H
#define HACKATHON_RANDOMBOT_H

#include "Player.h"


class RandomBot : public Player, std::enable_shared_from_this<RandomBot>
{
  public:
    RandomBot(const std::string &name, const int &id, const BoardSides &startSide);

    std::shared_ptr<GameDecision> getGameDecision(std::shared_ptr<GameField const> gameField) override;
};

#endif // HACKATHON_RANDOMBOT_H
