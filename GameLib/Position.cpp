#include "Position.h"

#include "../Graph/Graph.h"

Position::Position(Coordinate const & coordinate, Combinatorics::Vertex & vertex)
    : Position(coordinate.x(),coordinate.y(),vertex)
{}

Position::Position(int x, int y, Combinatorics::Vertex &vertex):Coordinate(x,y), m_vertex(vertex)
{}

Combinatorics::Vertex const & Position::getVertex() const
{
    return m_vertex;
}

Combinatorics::Vertex  & Position::getVertex()
{
    return m_vertex;
}

std::string Position::toString() const
{
    // you might want to adapt this method so that the field is not always empty
    return "o";
}

bool Position::operator==(const Position &other) const
{
    return Coordinate::operator==(other) && m_vertex.getId() == other.m_vertex.getId();
}

bool Position::operator==(const Coordinate &other)  const
{
    return false;
}
