#include "BonusEffect.hpp"

void BonusLevel::applyEffect(AntHill &destination)
{
    destination.setLevel();
}

int BonusLevel::getPrice(){
    return price;
}

void BonusLevel::setPrice(int new_price){
    price = new_price;
}



void BonusMoreAnts::applyEffect(AntHill &destination)
{
    // Implementace efektu "více Mravenců (max. hodnota)"
    destination.setMaxAnts();
}

int BonusMoreAnts::getPrice(){
    return price;
}

void BonusMoreAnts::setPrice(int new_price){
    price = new_price;
}



void BonusFasterProduction::applyEffect(AntHill &destination)
{
    // Implementace efektu "rychlejší produkce"
    destination.setproduction();
}
int BonusFasterProduction::getPrice(){
    return price;
}

void BonusFasterProduction::setPrice(int new_price){
    price = new_price;
}



void BonusStrongerAnts::applyEffect(AntHill &destination)
{
    // Implementace efektu "Silnější Mravenci"
    destination.setattack();
}

int BonusStrongerAnts::getPrice(){
    return price;
}

void BonusStrongerAnts::setPrice(int new_price){
    price = new_price;
}



void BonusDefendAnts::applyEffect(AntHill &destination)
{
    // Implementace efektu "silnější obrana mravencu"
    destination.setdefend();
}
int BonusDefendAnts::getPrice(){
    return price;
}

void BonusDefendAnts::setPrice(int new_price){
    price = new_price;
}