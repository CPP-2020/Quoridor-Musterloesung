//
// Created by bened on 23.07.2020.
//

#include "GameHost.h"

GameHost::GameHost(std::shared_ptr<Ui> &ui, std::vector<std::shared_ptr<Player>> &players)
        : ui(ui)
        , players(players)
{
}

void GameHost::startGame()
{
    gameRules = std::make_shared<GameRules>();
    gameField = std::make_shared<GameField>();

    int currentPlayerIndex = 0;

    if (players.size() != 2)
    {
        ui->showMessage("Exactly two players are required!");
    }

    placePlayersOnField();

    ui->drawGame(gameField);

    while (true)
    {
        const auto currentPlayer = players[currentPlayerIndex];

        bool decisionValid = false;

        while (!decisionValid)
        {
            auto gameDecision = currentPlayer->getGameDecision(gameField);

            decisionValid = gameDecision->isValidMove(currentPlayer->getPlayerData(), gameField);

            if (decisionValid)
            {
                gameDecision->executeMove(currentPlayer->getPlayerData(), gameField);
            }
        }

        ui->drawGame(gameField);

        const bool win = gameRules->didPlayerWin(currentPlayer->getPlayerData(), gameField);

        if (win)
        {
            ui->showWinnerMessage(currentPlayer->getPlayerData());
            break;
        }
        currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
    }
}

void GameHost::placePlayersOnField() const
{
    int height = gameField->getHeight();
    int width = gameField->getWidth();

    gameField->setPlayerPosition(players[0]->getPlayerData(),
                                 std::make_shared<Coordinate>(0, height / 2));
    players[0]->getPlayerData()->setStartSide(BoardSides::Left);

    gameField->setPlayerPosition(players[1]->getPlayerData(),
                                 std::make_shared<Coordinate>(width - 1, height / 2));
    players[1]->getPlayerData()->setStartSide(BoardSides::Right);
}
