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

std::shared_ptr<GameDecision> HumanPlayer::getGameDecision(
    std::shared_ptr<GameField const> gameField)
{
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
    std::shared_ptr<GameField const> gameField)
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
    std::shared_ptr<GameField const> gameField)
{
    bool correctPlacement = false;
    BorderOrientation borderOrientation;

    Coordinate *coordinate;

    int move = ui->showMultipleChoice("How would you like to place the border?",
                                      {"Vertical", "Horizontal"});

    if (move == 1)
    {
        borderOrientation = BorderOrientation::Vertical;
    }
    else if (move == 2)
    {
        borderOrientation = BorderOrientation::Horizontal;
    }

    int XborderPlacement =
        ui->showMultipleChoice("Where would you like to place the border (x value)?",
                               {"1", "2", "3", "4", "5", "6", "7", "8"});

    int YborderPlacement =
        ui->showMultipleChoice("Where would you like to place the border (y value)?",
                               {"1", "2", "3", "4", "5", "6", "7", "8"});

    while (1)
    {
        coordinate = new Coordinate(XborderPlacement - 1, YborderPlacement - 1);

        if (gameField->isValidCoordinate(*coordinate))
        {
            auto borderDesicion =
                std::make_shared<PlaceBorderDecision>(borderOrientation, *coordinate);

            if (borderDesicion->isValidMove(playerData, gameField))
            {
                return borderDesicion;
            }
        }

        XborderPlacement =
            ui->showMultipleChoice("This placement is invalid! Please select another x value:?",
                                   {"1", "2", "3", "4", "5", "6", "7"});
        YborderPlacement =
            ui->showMultipleChoice("This placement is invalid! Please select another y value:?",
                                   {"1", "2", "3", "4", "5", "6", "7"});
    }
}
