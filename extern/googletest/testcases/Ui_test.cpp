#include "gtest/gtest.h"

#include "../../../GameLib/ConsoleUi.h"
#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/GameField.h"
#include "../../../GameLib/Ui.h"

#include <memory>

TEST(UiTest, PleaseDrawABeautifulGameField)
{
	auto gameField = std::make_shared<GameField>(9, 9);
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
	gameField->setPlayerPosition(playerData, std::make_shared<Coordinate>(0, 0));

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

	ConsoleUi ui;

    std::cout << "====" << std::endl;
    ui.drawGame(gameField);
    std::cout << "====" << std::endl;

    ASSERT_TRUE(true);
}
