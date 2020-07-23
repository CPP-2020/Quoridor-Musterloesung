//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMEDECISION_H
#define HACKATHON_GAMEDECISION_H

#include "GameField.h"

class Player;
class GameField;

class GameDecision {
public:
	GameDecision(std::shared_ptr<const Player> player);

    virtual bool isValidMove(std::shared_ptr<const GameField> gameField) const = 0;
    virtual void executeMove(std::shared_ptr<GameField> gameField) = 0;

protected:
	std::shared_ptr<Player> player;
};


#endif //HACKATHON_GAMEDECISION_H
