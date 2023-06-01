#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

#include "AntHill.hpp"
#include "Ant.hpp"
#include "Position.hpp"
#include "Obstacles.hpp"

using namespace std;

class Board
{
private:
    // Interní datové struktury pro reprezentaci desky
    vector<Ant> Ants_onBoard;            // mravenci na desce
    vector<AntHill> AntsHill_onBoard;    // mraveniste na desce
    vector<Obstacles> Obstacles_onBoard; // prekazky na desce
    int x_board;
    int y_board;
public:
    Board();
    Board(std::vector<AntHill> antHills, std::vector<Obstacles> obstacles);
    void loadMap(string name_of_map);                                 // nahraje mapu
    void placeAntHill(AntHill *antHill, const Position &position);       // položi mraveniste kde ma byt
    void placeObstacles(Obstacles *obstacles, const Position &position); // polozi prekazky tam kde ma byt
    void moveAnt(Ant *ant, const Position &newPosition);                 // pohyb mravencu
    void removeAnt(Ant *ant);                                            // odstraneni mravencu
    void printBoard();
};

#endif // BOARD_H