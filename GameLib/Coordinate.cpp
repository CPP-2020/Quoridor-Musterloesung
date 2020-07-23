//
// Created by danie on 20.07.2020.
//

#include "Coordinate.h"

bool Coordinate::operator==(const Coordinate &other) const
{
    return x() == other.x() && y() == other.y();
}

Coordinate::Coordinate(int x, int y) : m_x(x), m_y(y)
{}

Coordinate Coordinate::getLeftCoordinate() const
{
    return Coordinate(x()-1, y());
}

Coordinate Coordinate::getAboveCoordinate() const
{
    return Coordinate(x(), y()+1);
}

Coordinate Coordinate::getRightCoordinate() const
{
    return Coordinate(x()+1, y());
}

Coordinate Coordinate::getBelowCoordinate() const
{
    return Coordinate(x(), y()-1);
}

int Coordinate::x() const
{
    return m_x;
}

int Coordinate::y() const
{
    return m_y;
}

std::ostream & operator<<(std::ostream & out, Coordinate const & coord)
{
    out << "("<< coord.x() << ","<< coord.y() <<")";
    return out;
}
