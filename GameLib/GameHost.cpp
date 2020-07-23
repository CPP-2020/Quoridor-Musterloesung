//
// Created by bened on 23.07.2020.
//

#include "GameHost.h"

GameHost::GameHost(std::shared_ptr<Ui>& ui, std::vector<std::shared_ptr<Player>>& players)
	:ui(ui)
	,players(players)
{

}

void GameHost::startGame() 
{
	gameRules = std::make_shared<GameRules>();
    gameField = std::make_shared<GameField>();

	int currentPlayerIndex = 0;

	ui->drawGame(gameField);

	while (true)  //Zeit für ein D D D D DUELL
	{
		const auto currentPlayer = players[currentPlayerIndex];

		//currentPlayer->getGameDecision(gameField);

		ui->drawGame(gameField);

		const bool win = gameRules->didPlayerWin(currentPlayer, gameField);

		if (win)
		{
			ui->showWinnerMessage(currentPlayer);
			break;
		}
		currentPlayerIndex = (currentPlayerIndex + 1) % 2;
	}
	
}
