#ifndef OBSTACLES_H
#define OBSTACLES_H

#include "ObjectOnBoard.hpp"
#include "Position.hpp"
#include <memory>
#include<iostream>
#include <vector>

using namespace std;
//prekazky na mape
class Obstacles : public ObjectOnBoard{
private:
Position position;
    // Vlastnosti překážek
public:
    Obstacles();
    Position getPositon() const;
    void print() override;
    bool IsPassable() const override;
    void setPassable(bool pruchod) override;


};

class EmptySpace : public ObjectOnBoard {
public:
    EmptySpace();
    void print() override;
    bool IsPassable() const override;
    void setPassable(bool pruchod) override;

};

#endif  // OBSTACLES_H