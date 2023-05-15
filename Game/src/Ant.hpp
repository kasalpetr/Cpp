#ifndef ANT_H
#define ANT_H

#include "AntHill.hpp"
#include "AntBehaviorABS.hpp"

class Ant
{
private:
    // Vlastnosti mravence
    int id;
    int level; // level mravence
    int strenght; // sila mravence
    int defend; // obrana sila mravence
    AntHill home; //mraveniste mravence
public:
    Ant(int id, int level, int strenght, int defend);
    void moveTo(const AntHill &target); //pohyb mravence
    void attack(const AntHill &target); // utok mravence
    void defend(); // obrana
    void specialAbility(AntBehaviorABS &ability){
        ability.ApplyType();
    } // specialni schopnosti(utocnik, obrance, rychlejsi mravenec)
};

#endif // ANT_H
