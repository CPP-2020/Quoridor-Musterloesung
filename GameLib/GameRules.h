//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMERULES_H
#define HACKATHON_GAMERULES_H

#include <memory>

class Player;
class GameField;

class GameRules {
public:
	bool didPlayerWin(std::shared_ptr<const Player> player, std::shared_ptr<const GameField> gameField);
};


#endif //HACKATHON_GAMERULES_H
