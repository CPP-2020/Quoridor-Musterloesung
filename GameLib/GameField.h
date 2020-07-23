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
    std::string toString() const;

    const Position & getPosition(Coordinate const & coordinates) const;

    const Position &getPlayerPosition(std::shared_ptr<PlayerId const> const &playerId) const;

private:
    std::map<std::shared_ptr<PlayerId const>, Position const &> m_playerPositions;

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
    void printDelimiter(std::string & result, Coordinate const & coordinate) const;
    void printContent(std::string & result, Coordinate const & coordinate) const;
    std::array<std::array<std::unique_ptr<Position>, s_height>, s_width> m_field;

    const Position &at(int x, int y) const;
};
