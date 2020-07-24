//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMEHOST_H
#define HACKATHON_GAMEHOST_H


#include "Ui.h"
#include "Player.h"
#include "GameRules.h"
#include <memory>
#include <vector>

class GameHost {
public:

    GameHost(std::shared_ptr<Ui> &ui, std::vector<std::shared_ptr<Player>> &players);

    std::shared_ptr<Player> startGame(int fieldHeight, int fieldWidth);

private:
    std::shared_ptr<Ui> ui;
    std::vector<std::shared_ptr<Player>>& players;
    std::shared_ptr<GameRules> gameRules;
    std::shared_ptr<GameField> gameField;

    void placePlayersOnField() const;
};


#endif //HACKATHON_GAMEHOST_H
