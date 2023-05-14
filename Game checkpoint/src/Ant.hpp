#ifndef ANT_H
#define ANT_H

#include "AntHill.hpp"
#include "AntBehaviorABS.hpp"

class Ant
{
private:
    // Vlastnosti mravence
    int id;
    int level;
    int strenght;
    int defend;
public:
    Ant(int id, int level, int strenght, int defend);
    void moveTo(const AntHill &target);
    void attack(const AntHill &target);
    void defend();
    void specialAbility(AntBehaviorABS &ability);
};

#endif // ANT_H
