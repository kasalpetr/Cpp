#include "Ant.hpp"

Ant::Ant(int id, int level, int strength, int defend)
    : id_Ant(id), level_Ant(level), strenght_Ant(strength), defend_Ant(defend)
{
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
void Ant::print(){
    
}

void Ant::setPassable(bool pruchod)
{
}

bool Ant::IsPassable() const{
    return true;
}
