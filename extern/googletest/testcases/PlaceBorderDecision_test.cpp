//
// Created by bened on 23.07.2020.
//

#include "../../../GameLib/DummyPlayer.h"
#include "../../../GameLib/PlaceBorderDecision.h"
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

    gameField->setBorderBetweenCoordinates({0, 0}, {1, 0});
    gameField->setBorderBetweenCoordinates({0, 0}, {0, 1});

    PlaceBorderDecision placeBorderDecision(BorderOrientation::Vertical, Coordinate(8, 8));
    ASSERT_FALSE(placeBorderDecision.isValidMove(playerData, gameField));

    placeBorderDecision = PlaceBorderDecision(BorderOrientation::Horizontal, Coordinate(0, 0));
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
