#ifndef BONUSEFFECTABS_H
#define BONUSEFFECTABS_H

#include "AntHill.hpp"

class BonusEffectABS {
private:
    // Vlastnosti bonusového efektu
public:
    virtual void applyEffect(AntHill &destination) = 0; //přida effect danému mravenisti
    virtual int getPrice() = 0; //přida effect danému mravenisti
    virtual void setPrice(int new_price) = 0; //přida effect danému mravenisti
};

#endif  // BONUSEFFECTABS_H
