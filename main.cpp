#include "GameLib/GameField.h"
#include "GameLib/GameHost.h"
#include "GameLib/HumanPlayer.h"
#include "GameLib/Player.h"
#include "GameLib/RandomBot.h"
#include "GameLib/Ui.h"

#include <memory>

void startGame(std::shared_ptr<Ui> ui);
std::shared_ptr<Player> getPlayerByUserChoice(std::shared_ptr<Ui> ui, int playerId);

int main()
{
    auto ui = std::make_shared<Ui>();    
    
    bool exit = false;

    while (!exit)
    {
        int choice =
            ui->showMultipleChoice("What would you like to do?", { "Start game", "Exit game" });

        if (choice == 1)
        {
            startGame(ui);
        }
        else
        {
            exit = true;
        }
    }
    return 0;
}

void startGame(std::shared_ptr<Ui> ui)
{
    std::vector<std::shared_ptr<Player>> players;

    players.push_back(getPlayerByUserChoice(ui, 1));
    players.push_back(getPlayerByUserChoice(ui, 2));

    std::shared_ptr<GameHost> gameHost = std::make_shared<GameHost>(ui, players);
    gameHost->startGame();
}


std::shared_ptr<Player> getPlayerByUserChoice(std::shared_ptr<Ui> ui, int playerId) 
{
    std::string message;
    //auto PlayerData = std::make_shared<Player>();

    if (playerId == 1)
    {
        message = "What should be the first player?";
    }
    else if (playerId == 2)
    {
        message = "What should be the second player?";
    }

    int choice = ui->showMultipleChoice(message, {"Human player", "Random player"});

    if (choice == 1)
    {
      return std::make_shared<HumanPlayer>("Player " + std::to_string(playerId), playerId, BoardSides::Right, ui);
    }

    if (choice == 2)
    {
        return std::make_shared<RandomBot>("Player " + std::to_string(playerId), playerId, BoardSides::Right);
    }

    if (choice == 3)
    {
    }

    if (choice == 4)
    {
    }

    return nullptr;
}
