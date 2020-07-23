#include "gtest/gtest.h"

#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/Ui.h"
#include "../../../GameLib/GameField.h"

#include <memory>

TEST(UiTest, PleaseDrawABeautifulGameField)
{
	auto gameField = std::make_shared<GameField>();
	std::shared_ptr<const Player> player = std::make_shared<const DummyPlayer>("Dummy", 0, BoardSides::Left);

	gameField->setPlayerPosition(player, std::make_shared<Coordinate>(0, 0));

	// Draw a large horizontal line
	for(int x = 0; x < gameField->getWidth() - 1; x++)
	{
		gameField->setBorderBetweenCoordinates({x, 1}, {x, 2});
	}

	// Draw a large vertical line
	for(int y = 1; y < gameField->getHeight() - 1; y++)
	{
		gameField->setBorderBetweenCoordinates({2, y}, {3, y});
	}

	// Draw a single horizontal line
	gameField->setBorderBetweenCoordinates({8, 6}, {8, 7});

	Ui ui;
	ui.drawGame(gameField);

	ASSERT_TRUE(true);
}
