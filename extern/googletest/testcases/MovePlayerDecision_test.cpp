#include "gtest/gtest.h"
#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/GameField.h"

#include "../../../GameLib/Ui.h"

#include <memory>

TEST(MovePlayerDecisionTest, When_MakeInvalidMoveToRight_Assert_isValidMoveReturnsFalse)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);

	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));
	gameField->setBorderBetweenCoordinates({0, 0}, {1, 0});
	gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});
	gameField->setBorderBetweenCoordinates({1, 0}, {1, 1});

	MovePlayerDecision decision(Direction::Right);

	ASSERT_FALSE(decision.isValidMove(player, gameField));
}

TEST(MovePlayerDecisionTest, When_ValidMoveToRight_Assert_isValidMoveReturnsTrue)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);

	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));

	MovePlayerDecision decision(Direction::Right);

	ASSERT_TRUE(decision.isValidMove(player, gameField));
}

TEST(MovePlayerDecisionTest, When_InValidMoveDown_Assert_isValidMoveReturnsFalse)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);

	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));
	gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});

	MovePlayerDecision decision(Direction::Down);

	ASSERT_FALSE(decision.isValidMove(player, gameField));
}

TEST(MovePlayerDecisionTest, When_ValidMoveDown_Assert_isValidMoveReturnsTrue)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);

	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));

	MovePlayerDecision decision(Direction::Down);

	ASSERT_TRUE(decision.isValidMove(player, gameField));
}
