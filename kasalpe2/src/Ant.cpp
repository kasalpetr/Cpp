#include "Ant.hpp"

Ant::Ant(AntHill &anthills) : homeAnthills(anthills)
{
    number_of_Ants = homeAnthills.getNumberOfAnts();
}

void Ant::print()
{
    if (homeAnthills.getOwner() == 1)
    {
        cout << "\x1B[42mO"; // Escape sekvence pro nastavení zeleného pozadí
        cout << "\x1B[0m";
    }
    else
    {
        cout << "\x1B[44mO"; // Escape sekvence pro nastavení modrého pozadí
        cout << "\x1B[0m";        // Resetování barev
    }
}

void Ant::setPassable(bool pruchod)
{
    
}

bool Ant::IsPassable() const
{
    return true;
}
