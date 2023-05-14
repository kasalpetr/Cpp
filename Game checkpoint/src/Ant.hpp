#ifndef ANT_H
#define ANT_H

#include "AntHill.hpp"

class Ant
{
private:
    // Vlastnosti mravence
    int level;
    int strenght;
    int defend;
public:
    Ant(int level, int strenght, int defend);
    void moveTo(const AntHill &target);
    void attack(const AntHill &target);
    void defend();
    void specialAbility();
};

#endif // ANT_H
