#include "gtest/gtest.h"
#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/GameField.h"

#include <memory>

TEST(MovePlayerDecisionTest, bla)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);
	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));
	gameField->setBorderBetweenCoordinates({0, 0}, {1, 0});
	MovePlayerDecision decision(Direction::Right);
	ASSERT_FALSE(decision.isValidMove(player, gameField));
}
