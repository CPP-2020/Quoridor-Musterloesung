//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLAYER_H
#define HACKATHON_PLAYER_H


#include <string>
#include "GameDecision.h"
#include "GameField.h"
#include <memory>

class Player {
public:
	Player(const std::string &name, const int &id);

	std::string getName() const;
	int getID() const;
	void setName(std::string newName);
	void setId(int newId);

	virtual GameDecision getGameDecision(std::shared_ptr<const GameField> gameField) = 0;

private:
	std::string name;
	int id;
};


#endif //HACKATHON_PLAYER_H
