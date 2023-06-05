#include "AntHill.hpp"

AntHill::AntHill() {}

AntHill::AntHill(int id, int x, int y)
    : id(id)
{
    position.setX(x);
    position.setY(y);
    if (id == 0)
    {
        Owner = 1;
    }
    if (id == 1)
    {
        Owner = 2;
    }
}

void AntHill::build()
{
    // Implementace postavení mraveniště při sestavování mapy
}

void AntHill::upgrade()
{
    // Implementace vylepšení levelu mraveniště
}

void AntHill::activateBonus(BonusEffectABS *bonus){}

Position AntHill::getPosition() const
{
    return position;
}

int AntHill::getId() const
{
    return id;
}

int AntHill::getOwner() const{
    return Owner;
}

int AntHill::getNumberOfAnts() const{
    return number_of_ants;
}

void AntHill::print()
{
    switch (Owner)
    {
    case 1: // hráč
        cout << "\x1B[42m" << id; // Escape sekvence pro nastavení zeleného pozadí
        cout << "\x1B[0m";   // Resetování barev
        break;
    case 2: // počítač
        cout << "\x1B[44m" << id; // Escape sekvence pro nastavení modrého pozadí
        cout << "\x1B[0m";   // Resetování barev
        break;
    default: // nikdo
        cout << "\x1B[41m" << id; // Escape sekvence pro nastavení červeného pozadí
        cout << "\x1B[0m";   // Resetování barev
        break;
    }
}

void AntHill::printAttackFrom(const vector<AntHill> &AntsHill_onBoard){

}

void AntHill::printAttackTo(const vector<AntHill> &AntsHill_onBoard){
    
}