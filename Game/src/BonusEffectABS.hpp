#ifndef BONUSEFFECTABS_H
#define BONUSEFFECTABS_H

#include "AntHill.hpp"

class BonusEffectABS {
private:
    // Vlastnosti bonusového efektu
public:
    virtual void applyEffect(AntHill &destination) = 0; //přida effect danému mravenisti
};

#endif  // BONUSEFFECTABS_H
