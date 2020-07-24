//
// Created by bened on 23.07.2020.
//

#include "DummyPlayer.h"
DummyPlayer::DummyPlayer(const std::shared_ptr<PlayerData> &playerData)
    : Player(playerData)
{
}

std::shared_ptr<GameDecision> DummyPlayer::getGameDecision(
    std::shared_ptr<const GameField> gameField) const
{
    return std::make_shared<MovePlayerDecision>(Direction::Down);
}
