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

	int currentPlayerIndex = 0;

	ui->drawGame();

	while (true)  //Zeit für ein D D D D DUELL
	{
		const auto currentPlayer = players[currentPlayerIndex];
		const auto nextPlayerIndex = (currentPlayerIndex + 1) %2;

		currentPlayer->getGameDecision();

		ui->drawGame(GameField);

		const bool win = gameRules->didPlayerWin(currentPlayer);

		if (win)
		{
			ui->showWinnerMessage(currentPlayer);
			break;
		}
		currentPlayerIndex = (currentPlayerIndex + 1) % 2;
	}
	
}
