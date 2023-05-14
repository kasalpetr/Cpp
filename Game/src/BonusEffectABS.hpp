#ifndef BONUSEFFECTABS_H
#define BONUSEFFECTABS_H

class BonusEffectABS {
private:
    // Vlastnosti bonusového efektu
    int price;
public:
    BonusEffectABS(int price);
    virtual void applyEffect() = 0; //přida effect danému mravenisti
};

#endif  // BONUSEFFECTABS_H
