#ifndef BONUSEFFECTABS_H
#define BONUSEFFECTABS_H

#include "AntHill.hpp"
/// @brief virtualni trida pro effecty
class BonusEffectABS {
private:
    // Vlastnosti bonusového efektu
public:
///přida effect danému mravenisti
    virtual void applyEffect(AntHill &destination) = 0; 
    /// @brief getter
    /// @return cena
    virtual int getPrice() = 0;
    ///nastavy novou cenu 
    virtual void setPrice(int new_price) = 0; 
};

#endif  // BONUSEFFECTABS_H
