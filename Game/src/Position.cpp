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