#ifndef BONUSEFFECT_H
#define BONUSEFFECT_H

#include "BonusEffectABS.hpp"
/// @brief Bonus na zvětšení levelu, cena se nastavuje při konfiguraci souboru
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

/// @brief Bonus na zvětšení maximálního počtu mravenců, cena se nastavuje při konfiguraci souboru
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
/// @brief Bonus na zvětšení produkce mravenců, cena se nastavuje při konfiguraci souboru
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

/// @brief Bonus na zvětšení útoků mravenců, cena se nastavuje při konfiguraci souboru
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
/// @brief Bonus na zvětšení Obrany mravenců, cena se nastavuje při konfiguraci souboru
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