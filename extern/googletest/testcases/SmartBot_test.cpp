//
// Created by bened on 24.07.2020.
//

#include "../../../GameLib/GameHost.h"
#include "../../../GameLib/NoOutputUi.h"
#include "../../../GameLib/RandomBot.h"
#include "../../../GameLib/SmartBot.h"
#include "gtest/gtest.h"

bool playGameWithSmartBotAndRandomBot()
{
    auto smartBot =
        std::make_shared<SmartBot>(std::make_shared<PlayerData>("Smart", 1, BoardSides::Right));

    auto randomBot =
        std::make_shared<RandomBot>(std::make_shared<PlayerData>("Random", 1, BoardSides::Right));

    std::vector<std::shared_ptr<Player>> players;
    players.push_back(randomBot);
    players.push_back(smartBot);

    std::shared_ptr<Ui> ui = std::make_shared<NoOutputUi>();

    GameHost host(ui, players);

    auto winner = host.startGame();

    return winner == smartBot;
}

TEST(SmartBotTest, When_RandomVsSmartBot_Assert_SmartBotWins)
{
    int tries = 100;
    int numberSmartBotWon = 0;
    for (int i = 0; i < tries; i++)
    {
        if (playGameWithSmartBotAndRandomBot())
        {
            numberSmartBotWon++;
        }
        else {
        }
    }

    std::cout << "Smart bot won " << numberSmartBotWon << " out of " << tries << std::endl;

    ASSERT_TRUE(numberSmartBotWon > tries * 0.95);
}
