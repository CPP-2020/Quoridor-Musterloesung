//
// Created by bened on 23.07.2020.
//

#include "Player.h"

Player::Player(std::shared_ptr<PlayerData> playerData)
        : playerData(playerData)
{
}

std::shared_ptr<PlayerData const> Player::getPlayerData() const
{
    return playerData;
}

std::shared_ptr<PlayerData> Player::getPlayerData()
{
    return playerData;
}
