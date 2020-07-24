#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/GameField.h"
#include "gtest/gtest.h"

#include "../../../GameLib/ConsoleUi.h"

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
	ASSERT_EQ(*gameField->getPlayerPosition(playerData), Coordinate(0, 1));
}

TEST(MovePlayerDecisionTest, When_OtherPlayerSurroundedByBorders_Assert_isValidMoveReturnsTrue)
{
	auto gameField = std::make_shared<GameField>();
	auto otherPlayer = std::make_shared<PlayerData>("Dummy1", 0, BoardSides::Right);
	auto playingPlayer = std::make_shared<PlayerData>("Dummy2", 1, BoardSides::Left);

	gameField->setPlayerPosition(otherPlayer, std::make_shared<Coordinate>(3, 3));
	gameField->setPlayerPosition(playingPlayer, std::make_shared<Coordinate>(4, 3));

	gameField->setBorderBetweenCoordinates({3, 2}, {3, 3});
	gameField->setBorderBetweenCoordinates({3, 3}, {3, 4});
	gameField->setBorderBetweenCoordinates({2, 3}, {3, 3});

	MovePlayerDecision decision(Direction::Left);

	ASSERT_FALSE(decision.isValidMove(playingPlayer, gameField));
}

TEST(MovePlayerDecisionTest, When_BorderInFrontOfOtherPlayerToJumpOver_Assert_walksAlternativeDirection)
{
	auto gameField = std::make_shared<GameField>();
	auto otherPlayer = std::make_shared<PlayerData>("Dummy1", 0, BoardSides::Right);
	auto playingPlayer = std::make_shared<PlayerData>("Dummy2", 1, BoardSides::Left);

	gameField->setPlayerPosition(otherPlayer, std::make_shared<Coordinate>(3, 3));
	gameField->setPlayerPosition(playingPlayer, std::make_shared<Coordinate>(4, 3));

	gameField->setBorderBetweenCoordinates({3, 3}, {3, 4});
	gameField->setBorderBetweenCoordinates({2, 3}, {3, 3});

	MovePlayerDecision decision(Direction::Left);

	ASSERT_TRUE(decision.isValidMove(playingPlayer, gameField));
	decision.executeMove(playingPlayer, gameField);
	ASSERT_EQ(*gameField->getPlayerPosition(playingPlayer), Coordinate(3, 2));
}

TEST(MovePlayerDecisionTest, When_JumpOverGameFieldBorder_Assert_walksAlternativeDirection)
{
	auto gameField = std::make_shared<GameField>();
	auto otherPlayer = std::make_shared<PlayerData>("Dummy1", 0, BoardSides::Right);
	auto playingPlayer = std::make_shared<PlayerData>("Dummy2", 1, BoardSides::Left);

	gameField->setPlayerPosition(otherPlayer, std::make_shared<Coordinate>(0, 0));
	gameField->setPlayerPosition(playingPlayer, std::make_shared<Coordinate>(1, 0));

	MovePlayerDecision decision(Direction::Left);

	ASSERT_TRUE(decision.isValidMove(playingPlayer, gameField));
	decision.executeMove(playingPlayer, gameField);
	ASSERT_EQ(*gameField->getPlayerPosition(playingPlayer), Coordinate(0, 1));
}
