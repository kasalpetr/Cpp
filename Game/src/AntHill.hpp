#ifndef ANTHILL_H
#define ANTHILL_H

#include "Position.hpp"
#include "ObjectOnBoard.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <limits>
using namespace std;

class AntHill : public ObjectOnBoard
{
private:
    // Vlastnosti mraveniště
    // bonusy
    int level = 1;
    int max_ants = 25;
    int production = 1;
    int defend = 10;
    int attack = 10;
   

    // promene
    int number_of_ants = 10;
    int Owner = 0; // 0 -> nikdy, 1 -> hráč, 2 -> počítač
    int id;
    Position position;
    bool isPassable = false;

    void changeOwner(int owner);

public:
    AntHill();
    AntHill(int id, int x, int y);
    void build(); // postaveni pri sestavovani mapy
    void ProduceAnts();
    Position getPosition() const;
    int getId() const;
    int getOwner() const;
    int getNumberOfAnts() const;
    int getMaxNumberOfAnts() const;
    int getlevel() const;
    int getDefend() const;
    int getAttack() const;

    void setLevel();
    void setproduction();
    void setMaxAnts();
    void setdefend();
    void setattack();
    void setPassable(bool pruchod) override;
    void support(AntHill &Attack_from);
    bool Attack(AntHill &Attack_from);
    // print metody
    void print() override;
    bool IsPassable() const override;

    int printAttackTo(const vector<AntHill> &AntsHill_onBoard);
    int printSupportTo(const vector<AntHill> &AntsHill_onBoard);
};

#endif // ANTHILL_H