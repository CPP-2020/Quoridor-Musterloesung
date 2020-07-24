#include "GameField.h"
#include "cassert"

using Combinatorics::Edge;
using Combinatorics::Graph;
using Combinatorics::Vertex;

GameField::GameField()
{
    for (int x = 0; x < s_width; x++)
    {
        for (int y = 0; y < s_height; y++)
        {
            m_field[x][y] = std::make_unique<Position>(Coordinate(x, y), m_graph.addVertex());
            if (y != 0)
            {
                m_graph.addEdge(getPosition(Coordinate(x, y)).getVertex(),
                                getPosition(Coordinate(x, y).getAboveCoordinate()).getVertex());
            }
            if (x != 0)
            {
                m_graph.addEdge(getPosition(Coordinate(x, y)).getVertex(),
                                getPosition(Coordinate(x, y).getLeftCoordinate()).getVertex());
            }
        }
    }
}

GameField::~GameField()
{
}

int GameField::getHeight() const
{
    return s_height;
}

int GameField::getWidth() const
{
    return s_width;
}

const Position &GameField::getPosition(Coordinate const &coordinate) const
{
    return *m_field.at(coordinate.x()).at(coordinate.y());
}

bool GameField::isOpenBelowCoordinate(const Coordinate &coordinate) const
{
    return m_graph.hasEdge(getPosition(coordinate).getVertex(),
                           getPosition(coordinate.getBelowCoordinate()).getVertex());
}

bool GameField::isOpenLeftOfCoordinate(const Coordinate &coordinate) const
{
    return m_graph.hasEdge(getPosition(coordinate).getVertex(),
                           getPosition(coordinate.getLeftCoordinate()).getVertex());
}

Position &GameField::getPosition(Coordinate const &coordinate)
{
    return *m_field.at(coordinate.x()).at(coordinate.y());
}

Combinatorics::EdgeId GameField::getEdgeIdBetweenCoordinates(Coordinate const &a,
                                                             Coordinate const &b) const
{
    return m_graph.findEdge(getPosition(a).getVertex(), getPosition(b).getVertex());
}

Combinatorics::Edge const &GameField::getEdgeBetweenCoordinates(Coordinate const &a,
                                                                Coordinate const &b) const
{
    assert(!noBorderBetweenCoordinates(a, b));
    return m_graph.getEdge(getEdgeIdBetweenCoordinates(a, b));
}

Combinatorics::Edge &GameField::getEdgeBetweenCoordinates(Coordinate const &a, Coordinate const &b)
{
    return const_cast<Combinatorics::Edge &>(
        static_cast<GameField const *>(this)->getEdgeBetweenCoordinates(a, b));
}

bool GameField::noBorderBetweenCoordinates(Coordinate const &a, Coordinate const &b) const
{
    return getEdgeIdBetweenCoordinates(a, b) != Graph::INVALID_EDGE_ID;
}

void GameField::setBorderBetweenCoordinates(const Coordinate &a, const Coordinate &b)
{
    auto edge = getEdgeIdBetweenCoordinates(a, b);

    if (edge == Graph::INVALID_EDGE_ID)
        return;

    m_graph.removeEdge(edge);
}

std::shared_ptr<Coordinate const> GameField::getPlayerPosition(
    const std::shared_ptr<const PlayerData> &player) const
{
    assert(m_playerPositions.find(player) != m_playerPositions.end());

	return m_playerPositions.at(player);
}

bool GameField::isOtherPlayerAtPosition(const std::shared_ptr<const PlayerData> &thisPlayer, const Coordinate &coordinate) const
{
	return std::any_of(m_playerPositions.begin(), m_playerPositions.end(),
					   [thisPlayer, coordinate] (auto const& x)
						{
							return x.first != thisPlayer && *x.second == coordinate;
						});
}

void GameField::setPlayerPosition(std::shared_ptr<const PlayerData> player,
                                  std::shared_ptr<const Coordinate> position)
{
    m_playerPositions[player] = position;
}

bool GameField::isValidCoordinate(const Coordinate &coordinate) const
{
    bool xValid = coordinate.x() >= 0 && coordinate.x() < s_width;
    bool yValid = coordinate.y() >= 0 && coordinate.y() < s_height;

    return xValid && yValid;
}

std::vector<std::shared_ptr<const PlayerData>> GameField::getAllPlayersOnField() const
{
    std::vector<std::shared_ptr<const PlayerData>> allPlayers;

    for (const auto &p: m_playerPositions)
    {
        allPlayers.push_back(p.first);
    }

    return allPlayers;
}

const Combinatorics::Graph& GameField::getGraph() const
{
    return m_graph;
}

