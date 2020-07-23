//
// Created by bened on 23.07.2020.
//

#include "DummyPlayer.h"
std::shared_ptr<GameDecision> DummyPlayer::getGameDecision(
    std::shared_ptr<const GameField> gameField)
{
    return std::make_shared<MovePlayerDecision>(Direction::Down);
}

DummyPlayer::DummyPlayer(const std::string &name, const int &id, const BoardSides &boardSides)
        : Player(name, id, boardSides)
{
}
