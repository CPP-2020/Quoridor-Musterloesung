//
// Created by bened on 23.07.2020.
//

#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/PlaceBorderDecision.h"
#include "../../../GameLib/Ui.h"
#include "gtest/gtest.h"
#include <memory>

TEST(PlaceBorderDecision, When_NoBordersOnField_Assert_PlaceBorderIsValidMove)
{
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    playerData->setRemainingBorders(10);

    auto gameField = std::make_shared<GameField>();

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(0, 0));
    ASSERT_TRUE(placeBorderDecision.isValidMove(playerData, gameField));

    placeBorderDecision = PlaceBorderDecision(BorderOrientation::Horizontal, Coordinate(0, 0));
    ASSERT_TRUE(placeBorderDecision.isValidMove(playerData, gameField));
}

TEST(PlaceBorderDecision, When_BordersOnField_Assert_PlaceBorderIsNoValidMove)
{
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    playerData->setRemainingBorders(10);

    auto gameField = std::make_shared<GameField>();

    gameField->setBorderBetweenCoordinates({0, 0}, {1, 0});
    gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(0, 0));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));

    placeBorderDecision = PlaceBorderDecision(BorderOrientation::Horizontal, Coordinate(0, 0));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));
}

TEST(PlaceBorderDecision, When_BordersOutOfField_Assert_PlaceBorderIsNoValidMove)
{
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    playerData->setRemainingBorders(10);

    auto gameField = std::make_shared<GameField>();

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(8, 8));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));
}

TEST(PlaceBorderDecision, When_NoBordersLeft_Assert_PlaceBorderIsNoValidMove)
{
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    playerData->setRemainingBorders(0);

    auto gameField = std::make_shared<GameField>();

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(0, 0));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));
}

TEST(PlaceBorderDecision, When_BorderCatchesPlayer_Assert_PlaceBorderIsNoValidMove)
{
    auto playerData = std::make_shared<PlayerData>("Dummy", 0, BoardSides::Right);
    playerData->setRemainingBorders(10);

    auto gameField = std::make_shared<GameField>();

    gameField->setPlayerPosition(playerData, std::make_shared<const Coordinate>(8, 3));

    gameField->setBorderBetweenCoordinates({3, 0}, {4, 0});
    gameField->setBorderBetweenCoordinates({3, 1}, {4, 1});
    gameField->setBorderBetweenCoordinates({3, 2}, {4, 2});
    // gameField->setBorderBetweenCoordinates({3, 3}, {0, 3}); // these are the borders which catch
    // the player gameField->setBorderBetweenCoordinates({3, 4}, {4, 4});
    gameField->setBorderBetweenCoordinates({3, 5}, {4, 5});
    gameField->setBorderBetweenCoordinates({3, 6}, {4, 6});
    gameField->setBorderBetweenCoordinates({3, 7}, {4, 7});
    gameField->setBorderBetweenCoordinates({3, 8}, {4, 8});

    Ui().drawGame(gameField);

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(3, 3));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));
}
