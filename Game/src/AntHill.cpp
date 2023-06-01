#include "AntHill.hpp"

AntHill::AntHill(){}

AntHill::AntHill(int id, int level, int max_ants)
    : id(id), level(level), max_ants(max_ants)
{
}

void AntHill::build()
{
    // Implementace postavení mraveniště při sestavování mapy
}

void AntHill::upgrade()
{
    // Implementace vylepšení levelu mraveniště
}

void AntHill::activateBonus(BonusEffectABS* bonus)
{
}
