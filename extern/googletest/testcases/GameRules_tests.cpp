//
// Created by bened on 23.07.2020.
//

#include "../../../GameLib/DummyPlayer.h"
#include "gtest/gtest.h"
#include <memory>

TEST(GameRulesTest, When_PlayerWonLeft_Assert_DidPlayerWinReturnsTrue)
{
    GameRules gameRules;

    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    auto gameField = std::make_shared<GameField>(9, 9);

    gameField->setPlayerPosition(playerData, std::make_shared<const Coordinate>(0, 5));

    ASSERT_TRUE(gameRules.didPlayerWin(playerData, gameField));
}

TEST(GameRulesTest, When_PlayerWonRight_Assert_DidPlayerWinReturnsTrue)
{
    GameRules gameRules;

    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Left);
    auto gameField = std::make_shared<GameField>(9, 9);

    gameField->setPlayerPosition(playerData,
                                 std::make_shared<const Coordinate>(gameField->getWidth() - 1, 5));

    ASSERT_TRUE(gameRules.didPlayerWin(playerData, gameField));
}

TEST(GameRulesTest, When_PlayerDidNotWin_Assert_DidPlayerWinReturnsFalse)
{
    GameRules gameRules;

    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    auto gameField = std::make_shared<GameField>(9, 9);

    gameField->setPlayerPosition(playerData, std::make_shared<const Coordinate>(1, 5));

    ASSERT_FALSE(gameRules.didPlayerWin(playerData, gameField));
}
