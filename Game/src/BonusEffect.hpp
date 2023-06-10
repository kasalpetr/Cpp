#ifndef BONUSEFFECT_H
#define BONUSEFFECT_H

#include "BonusEffectABS.hpp"


class BonusLevel : public BonusEffectABS {
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště"levnější mravenci"

public:
    void applyEffect(AntHill &destination) override;
};

class BonusMoreAnts : public BonusEffectABS {
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "více Mravenců (max. hodnota)"

public:
    void applyEffect(AntHill &destination) override;
};

class BonusFasterProduction : public BonusEffectABS {
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "rychlejší produkce"

public:
    void applyEffect(AntHill &destination) override;
};

class BonusStrongerAnts : public BonusEffectABS {
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "Silnejsi Mravenci"

public:
    void applyEffect(AntHill &destination) override;
};

class BonusDefendAnts : public BonusEffectABS {
private:
    // Vlastnosti konkrétního bonusového efektu mraveniště "obraný mravenci"

public:
    void applyEffect(AntHill &destination) override;
};

#endif  // BONUSEFFECT_H