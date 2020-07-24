#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/GameField.h"
#include "gtest/gtest.h"

#include "../../../GameLib/Ui.h"

#include <memory>

TEST(MovePlayerDecisionTest, When_MakeInvalidMoveToRight_Assert_isValidMoveReturnsFalse)
{
    auto gameField = std::make_shared<GameField>();
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);

    gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));
    gameField->setBorderBetweenCoordinates({0, 0}, {1, 0});
    gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});
    gameField->setBorderBetweenCoordinates({1, 0}, {1, 1});

    MovePlayerDecision decision(Direction::Right);

    ASSERT_FALSE(decision.isValidMove(playerData, gameField));
}

TEST(MovePlayerDecisionTest, When_ValidMoveToRight_Assert_isValidMoveReturnsTrue)
{
    auto gameField = std::make_shared<GameField>();
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);

    gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));

    MovePlayerDecision decision(Direction::Right);

    ASSERT_TRUE(decision.isValidMove(playerData, gameField));
}

TEST(MovePlayerDecisionTest, When_InValidMoveDown_Assert_isValidMoveReturnsFalse)
{
    auto gameField = std::make_shared<GameField>();
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);

    gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));
    gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});

    MovePlayerDecision decision(Direction::Down);

    ASSERT_FALSE(decision.isValidMove(playerData, gameField));
}

TEST(MovePlayerDecisionTest, When_ValidMoveDown_Assert_isValidMoveReturnsTrue)
{
    auto gameField = std::make_shared<GameField>();
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);

    gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));

    MovePlayerDecision decision(Direction::Down);

    ASSERT_TRUE(decision.isValidMove(playerData, gameField));
}

TEST(MovePlayerDecisionTest, When_ExecuteValidMove_Assert_isPlayerAtCorrectCoordinate)
{
	auto gameField = std::make_shared<GameField>();
	auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);

	gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));

	MovePlayerDecision decision(Direction::Down);

	ASSERT_TRUE(decision.isValidMove(playerData, gameField));
	decision.executeMove(playerData, gameField);
	std::cout << std::endl << "Y: " << gameField->getPlayerPosition(playerData)->y() << std::endl;
	ASSERT_EQ(gameField->getPlayerPosition(playerData), std::make_shared<Coordinate>(0, 1));
}

