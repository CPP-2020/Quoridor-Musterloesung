#include "GameLib\Ui.h"
#include "GameLib\GameHost.h"
#include "GameLib\Player.h"
//#include "GameLib\HumanPlayer.h"
#include "GameLib/GameField.h"
#include "GameLib/PlayerId.h"

#include <memory>

void startGame(std::shared_ptr<Ui> ui);
std::shared_ptr<Player> getPlayerByUserChoice(std::shared_ptr<Ui> ui, int playerNumber);

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


std::shared_ptr<Player> getPlayerByUserChoice(std::shared_ptr<Ui> ui, int playerNumber) //playerNumber instead of teamEnum
{
    std::string message;
    auto PlayerData = std::make_shared<PlayerId>();

    if (playerNumber == 1)
    {
        message = "What should be the first player?";
    }
    else if (playerNumber == 2)
    {
        message = "What should be the second player?";
    }

    int choice = ui->showMultipleChoice(message, {"Human player"});

    if (choice == 1)
    {
        PlayerData->setName("Player " + std::to_string(playerNumber));
        PlayerData->setId(playerNumber);
      //return std::make_shared<HumanPlayer>(playerData);
    }

    if (choice == 2)
    {
    }

    if (choice == 3)
    {
    }

    if (choice == 4)
    {
    }

    return nullptr;
}
