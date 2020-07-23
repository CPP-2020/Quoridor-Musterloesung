//
// Created by bened on 23.07.2020.
//

#include "GameDecision.h"
#include "GameField.h"
#include "Player.h"
#include <memory>

GameDecision::GameDecision(std::shared_ptr<const Player> player) : player(player)
{

}
