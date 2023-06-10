#include "Ant.hpp"

Ant::Ant(AntHill& anthills) : homeAnthills(anthills)
{
   number_of_Ants = homeAnthills.getNumberOfAnts();
   
}

void Ant::moveTo(const AntHill &target)
{
    // Implementace pohybu mravence
}

void Ant::attack(const AntHill &target)
{
    // Implementace útoku mravence
}

void Ant::defend()
{
    // Implementace obrany mravence
}

void Ant::specialAbility(AntBehaviorABS &ability)
{
    ability.ApplyType();
}
void Ant::print()
{
    cout << "\x1B[42mO"; // Escape sekvence pro nastavení zeleného pozadí
    cout << "\x1B[0m";
}

void Ant::setPassable(bool pruchod)
{
}

bool Ant::IsPassable() const
{
    return true;
}
