#ifndef BONUSEFFECT_H
#define BONUSEFFECT_H

#include "BonusEffectABS.hpp"

class BonusLevel : public BonusEffectABS
{
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště"levnější mravenci"
    int price = 0;

public:
    void applyEffect(AntHill &destination) override;
    int getPrice() override;
    void setPrice(int new_price) override;
};

class BonusMoreAnts : public BonusEffectABS
{
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "více Mravenců (max. hodnota)"
    int price = 0;

public:
    void applyEffect(AntHill &destination) override;
    int getPrice() override;
    void setPrice(int new_price) override;
};

class BonusFasterProduction : public BonusEffectABS
{
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "rychlejší produkce"
    int price = 0;

public:
    void applyEffect(AntHill &destination) override;
    int getPrice() override;
    void setPrice(int new_price) override;
};

class BonusStrongerAnts : public BonusEffectABS
{
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "Silnejsi Mravenci"
    int price = 0;

public:
    void applyEffect(AntHill &destination) override;
    int getPrice() override;
    void setPrice(int new_price) override;
};

class BonusDefendAnts : public BonusEffectABS
{
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "obraný mravenci"
    int price = 0;

public:
    void applyEffect(AntHill &destination) override;
    int getPrice() override;
    void setPrice(int new_price) override;
};

#endif // BONUSEFFECT_H