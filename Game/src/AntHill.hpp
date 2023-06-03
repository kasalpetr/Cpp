#ifndef ANTHILL_H
#define ANTHILL_H

#include "BonusEffectABS.hpp"
#include "Position.hpp"
#include <vector>
using namespace std;

class AntHill {
private:
    // Vlastnosti mraveniště
    int level = 1;
    int max_ants = 50;
    vector<BonusEffectABS*> bonuses;
    int id;
    Position position;
public:

    AntHill();
    AntHill(int id, int x, int y);
    void build(); //postaveni pri sestavovani mapy
    void upgrade(); //vylepseni lvl mraveniste
    void activateBonus(BonusEffectABS* Bonus);//pridani bonusu do vektoru
    Position getPosition() const;
    int getId() const;
};

#endif  // ANTHILL_H