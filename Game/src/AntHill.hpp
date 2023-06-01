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
    std::vector<BonusEffectABS*> bonuses;
public:
    AntHill();
    AntHill(int id, int level, int max_ants);
    void build(); //postaveni pri sestavovani mapy
    void upgrade(); //vylepseni lvl mraveniste
    void activateBonus(BonusEffectABS* Bonus);//pridani bonusu do vektoru
};

#endif  // ANTHILL_H