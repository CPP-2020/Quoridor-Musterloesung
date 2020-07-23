#pragma once

#include "Position.h"
#include "../Graph/Graph.h"
#include "PlayerId.h"

#include <array>
#include <memory>
#include <string>
#include <list>
#include <map>

class GameField {
public:
    GameField();
	virtual ~GameField();

	int getHeight() const;
	int getWidth() const;
    const Position & getPosition(Coordinate const & coordinates) const;
	bool isOpenBelowCoordinate(Coordinate const & coordinate) const;
	bool isOpenLeftOfCoordinate(Coordinate const & coordinate) const;

    std::shared_ptr<Position const> getPlayerPosition(std::shared_ptr<PlayerId const> const &playerId) const;

    void setPlayerPosition(std::shared_ptr<PlayerId const> &playerId, std::shared_ptr<Position const> position);

private:
    std::map<std::shared_ptr<PlayerId const>, std::shared_ptr<Position const>> m_playerPositions;

    Position & getPosition(Coordinate const & coordinates);
    // Returns corresponding EdgeId and Graph::INVALID_EDGE_ID if edge is already removed
    Combinatorics::EdgeId getEdgeIdBetweenCoordinates(Coordinate const & a, Coordinate const & b) const;
    Combinatorics::Edge const & getEdgeBetweenCoordinates(Coordinate const & a, Coordinate const & b) const;
    Combinatorics::Edge & getEdgeBetweenCoordinates(Coordinate const & a, Coordinate const & b);
    bool edgeBetweenCoordinatesExists(Coordinate const & a, Coordinate const & b) const;

    //////////////////
    /// Most likely you do not have to touch this
    Combinatorics::Graph m_graph;
    static constexpr int s_width {9};
    static constexpr int s_height {9};
    std::array<std::array<std::unique_ptr<Position>, s_height>, s_width> m_field;

    const Position &at(int x, int y) const;
};
