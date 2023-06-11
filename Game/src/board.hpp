#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <memory>
#include <limits>
#include <climits>
#include <queue>
#include <algorithm>
#include <thread>
#include <chrono>

#include "AntHill.hpp"
#include "Ant.hpp"
#include "Position.hpp"
#include "Obstacles.hpp"
#include "BonusEffect.hpp"
#include "Bot.hpp"

using namespace std;

class Board
{
private:
    string map;
    // Interní datové struktury pro reprezentaci desky
    vector<Ant> Ants_onBoard;                                  // mravenci na desce
    vector<AntHill> AntsHill_onBoard;                          // mraveniste na desce
    vector<Obstacles> Obstacles_onBoard;                       // prekazky na desce
    vector<vector<unique_ptr<ObjectOnBoard>>> board_for_print; // mapa 2d pole
    vector<int> bonuses;                                       // Vektor pro ukládání hodnot bonusů
    int x_board;
    int y_board;
    int test_counter = 0;
    Bot pocitac;

    int tree_level = 3;
    int money = 0;

    void placeAntHill();                                                                                    // položi mraveniste kde ma byt
    void placeObstacles(int x, int y);                                                                      // polozi prekazky tam kde ma
    bool checkplace(vector<AntHill> &AntsHill_onBoard, vector<Obstacles> &Obstacles_onBoard, int x, int y); // vraci false pokud jsou 2 veci na stejným miste
    bool checkAroundPlace(int x, int y, int new_x, int new_y);
    void MakeMove(int id_from, int id_to, int choice); // choice 0 -> attack, 1 -> support, 3 -> bonus for id_from
    void MakeMoveBonus(int id_from);
    void MakeMoveSupport(int id_from, int id_to);
    void MakeMoveAttack(int id_from, int id_to);
    vector<Position> FindWay(int id_from, int id_to);
    bool isValidPosition(int row, int col);
    void BoardForPrintMake(int x_board, int y_board);
    void AnalyseGameBot();

    // print metody
    void printAnthillOwner(int owner);
    char printChoiceOfMove();
    int printChoiceAnthillFrom();

public:
    Board();
    Board(std::vector<AntHill> antHills, std::vector<Obstacles> obstacles);
    void loadMap(string name_of_map); // nahraje mapu

    bool checkWin();

    // print metody
    void printBoard(); // tisk herní plochy
    void status();
    int printMove(); // tisk výběru tahu

    //getter
    vector<AntHill> getAntHill_on_board();
};

#endif // BOARD_H