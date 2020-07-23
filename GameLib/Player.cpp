//
// Created by bened on 23.07.2020.
//

#include "Player.h"

Player::Player(const std::string &name, const int &id, const BoardSides &startSide)
        : name(name)
        , id(id)
        , startSide(startSide)
{
}

std::string Player::getName() const
{
    return name;
}

int Player::getID() const
{
    return id;
}

BoardSides Player::getStartSide() const
{
    return startSide;
}
