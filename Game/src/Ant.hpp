#ifndef ANT_H
#define ANT_H

#include "AntHill.hpp"
#include "AntBehaviorABS.hpp"
#include "ObjectOnBoard.hpp"

class Ant : public ObjectOnBoard
{
private:
    // Vlastnosti mravenců
    int number_of_Ants;
    int level_Ant; // level mravenců
    int strenght_of_Ant; // sila mravenců
    int defend_of_Ant; // obrana sila mravenců
    AntHill& homeAnthills;
public:
    Ant(AntHill& anthills);
    void moveTo(const AntHill &target); //pohyb mravence
    void attack(const AntHill &target); // utok mravence
    void defend(); // obrana
    void specialAbility(AntBehaviorABS &ability); // specialni schopnosti(utocnik, obrance, rychlejsi mravenec)
    void print() override;
    bool IsPassable()const override;
    void setPassable(bool pruchod) override;


};

#endif // ANT_H
