//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMERULES_H
#define HACKATHON_GAMERULES_H

#include "PlayerData.h"
#include <memory>

class Player;
class GameField;

class GameRules {
public:
	bool didPlayerWin(std::shared_ptr<const PlayerData> player, std::shared_ptr<const GameField> gameField);
};


#endif //HACKATHON_GAMERULES_H
