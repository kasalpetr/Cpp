#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include "AntHill.hpp"
#include "Ant.hpp"
#include "Position.hpp"
#include "Obstacles.hpp"


using namespace std;


class Board {
private:
    // Interní datové struktury pro reprezentaci desky
    vector<Ant> Ants;
    vector<AntHill> AntsHill;
    vector<Obstacles> Obstacles;

public:
    Board(vector<AntHill> AntsHill, vector<Obstacles> Obstacles);
    void loadMap(const string& mapFile);
    void placeAntHill(AntHill* antHill, const Position& position);
    void placeObstacles(Obstacles* obstacles, const Position& position);
    AntHill* getAntHill(const Position& position);
    void moveAntHill(AntHill* antHill, const Position& newPosition);
    void removeAntHill(AntHill* antHill);
    vector<Ant*> getAnts(const Position& position);
    void moveAnt(Ant* ant, const Position& newPosition);
    void removeAnt(Ant* ant);
};

#endif  // BOARD_H