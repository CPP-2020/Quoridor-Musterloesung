//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_PLAYER_H
#define HACKATHON_PLAYER_H

#include "GameDecision.h"
#include "GameField.h"
#include "PlayerData.h"

#include <memory>
#include <string>

class Player {
public:
	Player(std::shared_ptr<PlayerData> playerData);
	virtual std::shared_ptr<GameDecision> getGameDecision(std::shared_ptr<GameField const> gameField) const = 0;

    std::shared_ptr<PlayerData const> getPlayerData() const;
    std::shared_ptr<PlayerData> getPlayerData();

  protected:
    std::shared_ptr<PlayerData> playerData;
};


#endif //HACKATHON_PLAYER_H
