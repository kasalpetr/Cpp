#include "Position.hpp"
Position::Position()
{
}

Position::Position(int x, int y)
{
    // Konstruktor
    this->x = x;
    this->y = y;
}

bool Position::operator==(const Position &other) const
{
    return (x == other.x) && (y == other.y);
}

bool Position::operator!=(const Position &other) const
{
    return !(*this == other);
}

bool Position::operator<(const Position &other) const
{
    if (x != other.x)
    {
        return x < other.x;
    }
    return y < other.y;
}

int Position::getX() const
{
    return x;
}

int Position::getY() const
{
    return y;
}

void Position::setX(int x)
{
    this->x = x;
}

void Position::setY(int y)
{
    this->y = y;
}