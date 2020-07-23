//
// Created by bened on 23.07.2020.
//



#ifndef HACKATHON_GAMEHOST_H
#define HACKATHON_GAMEHOST_H

#include "Player.h"



class RandomBot : public Player, std::enable_shared_from_this<RandomBot>
{
  public:
    std::shared_ptr<GameDecision> getGameDecision(std::shared_ptr<GameField const> gameField) override;



};

#endif // HACKATHON_GAMEHOST_H
