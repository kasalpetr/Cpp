#include "AntHill.hpp"

AntHill::AntHill(){}

AntHill::AntHill(int id, int x, int y)
    : id(id)
{
 position.setX(x);
 position.setY(y);
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
