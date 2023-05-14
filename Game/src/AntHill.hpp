#ifndef ANTHILL_H
#define ANTHILL_H

#include <vector>
#include "BonusEffectABS.hpp"

class AntHill {
private:
    // Vlastnosti mraveniště
    int id;
    int level;
    int max_ants;
    vector<BonusEffectABS*> bonuses;
public:
    AntHill(int id, int level, int max_ants);
    void build();
    void upgrade();
    void activateBonus(BonusEffectABS* Bonus);
};

#endif  // ANTHILL_H