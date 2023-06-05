#ifndef ANTHILL_H
#define ANTHILL_H

#include "BonusEffectABS.hpp"
#include "Position.hpp"
#include "ObjectOnBoard.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include<limits>
using namespace std;

class AntHill : public ObjectOnBoard {
private:
    // Vlastnosti mraveniště
    int level = 1;
    int max_ants = 50;
    int number_of_ants = 25;
    int Owner = 0; // 0 -> nikdy, 1 -> hráč, 2 -> počítač
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
    int getOwner() const;
    int getNumberOfAnts() const;

    //print metody
    void print() override;
    int printAttackTo(const vector<AntHill> &AntsHill_onBoard);
    int printSupportTo(const vector<AntHill> &AntsHill_onBoard);

};

#endif  // ANTHILL_H