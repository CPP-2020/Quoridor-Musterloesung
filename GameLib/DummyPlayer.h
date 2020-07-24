//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_DUMMYPLAYER_H
#define HACKATHON_DUMMYPLAYER_H

#include "GameRules.h"
#include "MovePlayerDecision.h"
#include "Player.h"

#include <memory>
#include <string>

class DummyPlayer : public Player
{
  public:
    DummyPlayer(const std::shared_ptr<PlayerData> &playerData);
    std::shared_ptr<GameDecision> getGameDecision(
        std::shared_ptr<const GameField> gameField) const override;
};

#endif // HACKATHON_DUMMYPLAYER_H
