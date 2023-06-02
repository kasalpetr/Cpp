#ifndef ANTHILL_H
#define ANTHILL_H

#include <vector>
#include "BonusEffectABS.hpp"
#include "Position.hpp"


class AntHill {
private:
    // Vlastnosti mraveniště
    int level = 1;
    int max_ants = 50;
    // vector<BonusEffectABS> bonuses;
public:
    int id;
    Position position;
    AntHill();
    AntHill(int id, int x, int y);
    void build(); //postaveni pri sestavovani mapy
    void upgrade(); //vylepseni lvl mraveniste
    void activateBonus(BonusEffectABS* Bonus);//pridani bonusu do vektoru
};

#endif  // ANTHILL_H