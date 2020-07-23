//
// Created by bened on 23.07.2020.
//

#include "PlayerData.h"


PlayerData::PlayerData(const std::string &name, int id, BoardSides startSide)
    : name(name)
    , id(id)
    , startSide(startSide)
{
}

std::string PlayerData::getName() const
{
    return name;
}

int PlayerData::getID() const
{
    return id;
}

BoardSides PlayerData::getStartSide() const
{
    return startSide;
}

int PlayerData::getRemainingBorders() const
{
    return remainingBorders;
}
void PlayerData::setRemainingBorders(int borders)
{
	remainingBorders = borders;
}

bool PlayerData::operator==(const PlayerData &other)
{
	return id == other.id;
}

void PlayerData::setStartSide(BoardSides boardSide)
{
    startSide = boardSide;
}
