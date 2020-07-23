//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_GAMEHOST_H
#define HACKATHON_GAMEHOST_H


#include "Ui.h"
#include "Player.h"
#include "GameRules.h"

class GameHost {
public:
    GameHost(Ui& ui, std::vector<Player> players);

    void startGame();

private:
    std::shared_ptr<Ui> ui;
    std::vector<Player> players;
    std::shared_ptr<GameRules> gameRules;
    std::shared_ptr<GameField> gameField;
};


#endif //HACKATHON_GAMEHOST_H
