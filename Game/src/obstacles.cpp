#include "Obstacles.hpp"

Obstacles::Obstacles()
{
}

Position Obstacles::getPositon() const
{
    return position;
}

void Obstacles::print()
{

    cout << "\x1B[47m "; // Escape sekvence pro nastavení bílého pozadí
    cout << "\x1B[0m";   // Resetování barev
}

bool Obstacles::IsPassable() const
{
    return false;
}

void Obstacles::setPassable(bool pruchod)
{
}

EmptySpace::EmptySpace() {}

void EmptySpace::print()
{
    cout << " "; // Placeholder print statement for EmptySpace
}

bool EmptySpace::IsPassable() const
{
    return true;
}

void EmptySpace::setPassable(bool pruchod)
{
}