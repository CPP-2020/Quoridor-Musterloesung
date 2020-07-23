#include "HumanPlayer.h"
#include "Coordinate.h"
#include "MovePlayerDecision.h"
#include "PlaceBorderDecision.h"
#include "Ui.h"

//
// Created by bened on 23.07.2020.
//

HumanPlayer::HumanPlayer(const std::string &name,
                         const int &id,
                         const BoardSides &startSide,
                         std::shared_ptr<Ui> ui)
        : Player(name, id, startSide)
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
        if (moveDecision->isValidMove(shared_from_this(), gameField))
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

    int borderPlacement =
        ui->showMultipleChoice("Where would you like to place the border?", {"a", "b", "c"});

    while (1)
    {
        switch (borderPlacement)
        {
        case 1: {
            coordinate = new Coordinate(0, 0);
            break;
        }
        case 2: {
            coordinate = new Coordinate(4, 2);
            break;
        }
        case 3: {
            coordinate = new Coordinate(2, 4);
            break;
        }
        }

        if (gameField->isValidCoordinate( *coordinate))
        {
            auto borderDesicion =
                std::make_shared<PlaceBorderDecision>(borderOrientation, *coordinate);
            return borderDesicion;
        }

        ui->showMultipleChoice("This placement is invalid! Please select another one:?",
                               {"a", "b", "c"});
    }
}