#ifndef ANTHILL_H
#define ANTHILL_H

#include "Position.hpp"
#include "ObjectOnBoard.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <limits>
using namespace std;
/// @brief reprezentace mraveniste
class AntHill : public ObjectOnBoard
{
private:
    /// Vlastnosti mraveniště
    // bonusy
    int level = 1;
    int max_ants = 25;
    int production = 5;
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
    AntHill(); ///konstruktor
    AntHill(int id, int x, int y); ///konstruktor 
    /// vytvori tolik mravencu podle produkce
    void ProduceAnts(); 
    /// gettery 
    Position getPosition() const;
    int getId() const;
    int getOwner() const;
    int getNumberOfAnts() const;
    int getMaxNumberOfAnts() const;
    int getlevel() const;
    int getDefend() const;
    int getAttack() const;
    
    /// nastavovaní bonusu
    void setLevel();
    void setproduction();
    void setMaxAnts();
    void setdefend();
    void setattack();

    /// nacte nove hodnoty mraveniste -> použivano pri nahrávání hry
    void loadnewAntHills(int id, int level, int number_of_ants, int max_of_ants, int owner, int attack, int defend); 
    
    void setPassable(bool pruchod) override;
    /// @brief vypocet pro pocet mravencu pri podporeni mraveniste
    /// @param Attack_from mraveniste odkud se podporovalo
    void support(AntHill &Attack_from);
    /// @brief vypocet utoku pri utoku na mraveniste
    /// @param Attack_from mraveniste odkud bylo utoceno
    /// @return vraci true pokud bylo mraveniste obsazeno 
    bool Attack(AntHill &Attack_from);
    // print metody
    void print() override;
    bool IsPassable() const override;
    ///tiskne mraveniste kam se muze utocit
    int printAttackTo(const vector<AntHill> &AntsHill_onBoard);
    /// tiskne mraveniste kam se muze podporovat
    int printSupportTo(const vector<AntHill> &AntsHill_onBoard);
};

#endif // ANTHILL_H