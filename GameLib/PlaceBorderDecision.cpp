//
// Created by bened on 23.07.2020.
//

#include "PlaceBorderDecision.h"
#include "../Graph/Algorithm/BreadthFirstSearch.h"
#include "Player.h"
#include <assert.h>
#include <memory>

PlaceBorderDecision::PlaceBorderDecision(const BorderOrientation &orientation,
                                         const Coordinate &topLeftCoordinate)
        : topLeftCoordinate(topLeftCoordinate)
        , orientation(orientation)
{
}

bool PlaceBorderDecision::isValidMove(std::shared_ptr<const PlayerData> player,
                                      std::shared_ptr<const GameField> gameField) const
{
    bool validMove = true;

    validMove &= player->getRemainingBorders() > 0;

    auto topRightCoordinate = topLeftCoordinate.getRightCoordinate();
    auto bottomLeftCoordinate = topLeftCoordinate.getBelowCoordinate();
    auto bottomRightCoordinate = bottomLeftCoordinate.getRightCoordinate();

    validMove &= gameField->isValidCoordinate(topLeftCoordinate);
    validMove &= gameField->isValidCoordinate(topRightCoordinate);
    validMove &= gameField->isValidCoordinate(bottomLeftCoordinate);
    validMove &= gameField->isValidCoordinate(bottomRightCoordinate);

    if (!validMove)
    {
        return false;
    }

    for (const auto &p: gameField->getAllPlayersOnField())
    {
        validMove &= borderDoesNotCatchPlayer(gameField, p);
    }

    if (orientation == BorderOrientation::Horizontal)
    {
        validMove &=
            gameField->noBorderBetweenCoordinates(topLeftCoordinate, bottomLeftCoordinate) &&
            gameField->noBorderBetweenCoordinates(topRightCoordinate, bottomRightCoordinate);
    }

    if (orientation == BorderOrientation::Vertical)
    {
        validMove &= gameField->noBorderBetweenCoordinates(topLeftCoordinate, topRightCoordinate) &&
            gameField->noBorderBetweenCoordinates(bottomLeftCoordinate, bottomRightCoordinate);
    }

    return validMove;
}

void PlaceBorderDecision::executeMove(std::shared_ptr<PlayerData> player,
                                      std::shared_ptr<GameField> gameField)
{
    assert(isValidMove(player, gameField));

    auto topRightCoordinate = topLeftCoordinate.getRightCoordinate();
    auto bottomLeftCoordinate = topLeftCoordinate.getBelowCoordinate();
    auto bottomRightCoordinate = bottomLeftCoordinate.getRightCoordinate();

    if (orientation == BorderOrientation::Horizontal)
    {
        gameField->setBorderBetweenCoordinates(topLeftCoordinate, bottomLeftCoordinate);
        gameField->setBorderBetweenCoordinates(topRightCoordinate, bottomRightCoordinate);
    }

    if (orientation == BorderOrientation::Vertical)
    {
        gameField->setBorderBetweenCoordinates(topLeftCoordinate, topRightCoordinate);
        gameField->setBorderBetweenCoordinates(bottomLeftCoordinate, bottomRightCoordinate);
    }

    player->setRemainingBorders(player->getRemainingBorders() - 1);
}

bool PlaceBorderDecision::borderDoesNotCatchPlayer(std::shared_ptr<const GameField> gameField,
                                                   std::shared_ptr<const PlayerData> player) const
{
    std::set<Combinatorics::EdgeId> edgesOfBorder = getEdgesOfBorder(gameField);

    for (const auto &e: edgesOfBorder)
    {
        std::cout << gameField->getGraph().getEdge(e).getEndpoint1().getId() << std::endl;
        std::cout << gameField->getGraph().getEdge(e).getEndpoint2().getId() << std::endl;
        std::cout << e << std::endl;
    }

    int columnToCheck = -1;
    if (player->getStartSide() == BoardSides::Left)
    {
        columnToCheck = gameField->getWidth() - 1;
    }
    else if (player->getStartSide() == BoardSides::Right)
    {
        columnToCheck = 0;
    }

    auto &playerPosition = gameField->getPosition(*gameField->getPlayerPosition(player));

    Combinatorics::BreadthFirstSearch bfs(
        gameField->getGraph(), edgesOfBorder, playerPosition.getVertex());

    bool isSideReachable = false;

    for (int i = 0; i < gameField->getHeight(); i++)
    {
        isSideReachable |= bfs.is_reachable(gameField->getPosition({columnToCheck, i}).getVertex());
        if (isSideReachable)
        {
            auto vertices = bfs.getPath(gameField->getPosition({columnToCheck, i}).getVertex());

            for (const auto &v: vertices)
            {
                std::cout << v << std::endl;
            }
        }
    }

    return isSideReachable;
}

std::set<Combinatorics::EdgeId> PlaceBorderDecision::getEdgesOfBorder(
    const std::shared_ptr<const GameField> &gameField) const
{
    const Combinatorics::Graph &graph = gameField->getGraph();

    auto topRightCoordinate = topLeftCoordinate.getRightCoordinate();
    auto bottomLeftCoordinate = topLeftCoordinate.getBelowCoordinate();
    auto bottomRightCoordinate = bottomLeftCoordinate.getRightCoordinate();

    auto topLeftVertex = gameField->getPosition(topLeftCoordinate).getVertex();
    auto topRightVertex = gameField->getPosition(topRightCoordinate).getVertex();
    auto bottomLeftVertex = gameField->getPosition(bottomLeftCoordinate).getVertex();
    auto bottomRightVertex = gameField->getPosition(bottomRightCoordinate).getVertex();

    Combinatorics::EdgeId edge1 = Combinatorics::Graph::INVALID_EDGE_ID;
    Combinatorics::EdgeId edge2 = Combinatorics::Graph::INVALID_EDGE_ID;

    if (orientation == BorderOrientation::Horizontal)
    {
        edge1 = graph.findEdge(topLeftVertex, bottomLeftVertex);
        edge2 = graph.findEdge(topRightVertex, bottomRightVertex);
    }
    else if (orientation == BorderOrientation::Vertical)
    {
        edge1 = graph.findEdge(topLeftVertex, topRightVertex);
        edge2 = graph.findEdge(bottomLeftVertex, bottomRightVertex);
    }

    std::set<Combinatorics::EdgeId> edgesOfBorder;

    if (edge1 != Combinatorics::Graph::INVALID_EDGE_ID &&
        edge2 != Combinatorics::Graph::INVALID_EDGE_ID)
    {
        edgesOfBorder.insert(edge1);
        edgesOfBorder.insert(edge2);
    }

    return edgesOfBorder;
}
