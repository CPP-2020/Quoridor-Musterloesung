#include "HumanPlayer.h"
#include "MovePlayerDecision.h"
#include "PlaceBorderDecision.h"
#include "Ui.h"

//
// Created by bened on 23.07.2020.
//

HumanPlayer::HumanPlayer(std::shared_ptr<PlayerData> playerData, std::shared_ptr<Ui> ui)
        : Player(playerData)
        , ui(ui)
{
}

// Choose if the player wants to move or to place a border
std::shared_ptr<GameDecision> HumanPlayer::getGameDecision(
    std::shared_ptr<GameField const> gameField) const
{
    ui->showMessage(playerData->getName() + " its your turn! You have " +
                    std::to_string(playerData->getRemainingBorders()) + " remaining borders.");

    // If the player has no remaining borders, he can only move
    if (playerData->getRemainingBorders() < 1)
    {
        ui->showMessage("You have no remaining borders, so you can only move!");
        return getMoveDecision(gameField);
    }
    int desicion =
        ui->showMultipleChoice("What would you like to do?", {"Make a move", "Place border"});

    if (desicion == 1)
    {
        return getMoveDecision(gameField);
    }
    else if (desicion == 2)
    {
        return getBorderDecision(gameField);
    }

    return nullptr;
}
std::shared_ptr<GameDecision> HumanPlayer::getMoveDecision(
    std::shared_ptr<GameField const> gameField) const
{
    Direction moveDirection;

    int move =
        ui->showMultipleChoice("How would you like to move?", {"Up", "Down", "Left", "Right"});

    while (1)
    {
        switch (move)
        {
        case 1: {
            moveDirection = Direction::Up;
            break;
        }
        case 2: {
            moveDirection = Direction::Down;
            break;
        }
        case 3: {
            moveDirection = Direction::Left;
            break;
        }
        case 4: {
            moveDirection = Direction::Right;
            break;
        }
        }

        auto moveDecision = std::make_shared<MovePlayerDecision>(moveDirection);
        if (moveDecision->isValidMove(playerData, gameField))
        {
            return moveDecision;
        }

        move = ui->showMultipleChoice("Move is inavlid! Please select another one:",
                                      {"Up", "Down", "Left", "Right"});
    }
}
std::shared_ptr<GameDecision> HumanPlayer::getBorderDecision(
    std::shared_ptr<GameField const> gameField) const
{
    bool correctPlacement = false;
    BorderOrientation borderOrientation;

    Coordinate *coordinate;

    int XborderPlacement = ui->showMultipleIntChoice(
        "Where would you like to place the border (x value)?", 1, gameField->getWidth());

    int YborderPlacement = ui->showMultipleIntChoice(
        "Where would you like to place the border (y value)?", 1, gameField->getHeight());

    int orientation = ui->showMultipleChoice("How would you like to place the border?",
                                             {"Vertical", "Horizontal"});

    if (orientation == 1)
    {
        borderOrientation = BorderOrientation::Vertical;
    }
    else if (orientation == 2)
    {
        borderOrientation = BorderOrientation::Horizontal;
    }

    while (1)
    {                                               //-1 because of array indizies
        coordinate = new Coordinate((XborderPlacement - 1), (YborderPlacement - 1));

        if (gameField->isValidCoordinate(*coordinate))
        {
            auto borderDesicion =
                std::make_shared<PlaceBorderDecision>(borderOrientation, *coordinate);

            if (borderDesicion->isValidMove(playerData, gameField))
            {
                return borderDesicion;
            }
        }

        XborderPlacement = ui->showMultipleIntChoice(
            "Where would you like to place the border (x value)?", 1, gameField->getWidth());

        YborderPlacement = ui->showMultipleIntChoice(
            "Where would you like to place the border (y value)?", 1, gameField->getHeight());
    }
}
