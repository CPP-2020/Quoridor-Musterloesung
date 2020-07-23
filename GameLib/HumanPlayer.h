//
// Created by bened on 23.07.2020.
//

#ifndef HACKATHON_HUMANPLAYER_H
#define HACKATHON_HUMANPLAYER_H

#include "Player.h"

class Ui;

class HumanPlayer : public Player, std::enable_shared_from_this<HumanPlayer>
{
public:
	HumanPlayer(const std::string &name, const int &id, const BoardSides &startSide, std::shared_ptr<Ui> ui);

	std::shared_ptr<GameDecision> getGameDecision(std::shared_ptr<GameField const> gameField) override;

private:
	std::shared_ptr<Ui> ui;
	std::shared_ptr<GameDecision> getMoveDecision(std::shared_ptr<GameField const> gameField);
	std::shared_ptr<GameDecision> getBorderDecision(std::shared_ptr<GameField const> gameField);

};


#endif //HACKATHON_HUMANPLAYER_H
