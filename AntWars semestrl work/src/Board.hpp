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
#include "obstacles.hpp"
#include "BonusEffect.hpp"
#include "Bot.hpp"

using namespace std;
/// @brief hlavní třída kde se děje většina věcí hlavně výpisy 
class Board
{
private:
    string map;
    // Interní datové struktury pro reprezentaci desky
    ///mraveniste na plose jsou serazeny dle id dá se tedy pritupovat do vectoru pomocí id jako iteratoru
    vector<AntHill> AntsHill_onBoard;                          // mraveniste na desce
    ///prekazky na plose
    vector<Obstacles> Obstacles_onBoard;                       // prekazky na desce
    ///polymorfní dvou rozměrné pole pro zefektivnění tisku
    vector<vector<unique_ptr<ObjectOnBoard>>> board_for_print; // mapa 2d pole
    /// Vektor pro ukládání hodnot bonusů
    vector<int> bonuses;                                       
    int x_board;
    int y_board;
    int test_counter = 0;
    /// @brief bot -> pocitac
    Bot pocitac;

    int tree_level = 3;
    int money = 0;
    /// polozi prekazky do 2d mapy na pozice x a y
    void placeObstacles(int x, int y);                                                                      // polozi prekazky tam kde ma
    ///  vraci false pokud jsou 2 veci na stejným miste a v okoli 3*3 neco je
    bool checkplace(vector<AntHill> &AntsHill_onBoard, vector<Obstacles> &Obstacles_onBoard, int x, int y); // vraci false pokud jsou 2 veci na stejným miste
    ///kontroluje okoli 3*3
    bool checkAroundPlace(int x, int y, int new_x, int new_y);
    ///vykonava tah dle choice
    void MakeMove(int id_from, int id_to, int choice); // choice 0 -> attack, 1 -> support, 3 -> bonus for id_from
    ///provede tah bonus na mravenisti id_from zaroven si tady v té metode vyberu daný bonus
    int MakeMoveBonus(int id_from);
    /// @brief provedu podporu
    /// @param id_from z jakeho mraveniste 
    /// @param id_to do jakeho mraveniste
    void MakeMoveSupport(int id_from, int id_to);
    /// @brief provedu utok
    /// @param id_from z jakeho mraveniste
    /// @param id_to do jakeho mraveniste
    void MakeMoveAttack(int id_from, int id_to);
    ///bfs algoritmus na hledání nejkratsi cesty mezi mravensti, cesty se nehledají uhlopričně
    vector<Position> FindWay(int id_from, int id_to);
    /// kontorla pruchodnosti na dane pozici 
    bool isValidPosition(int row, int col);
    /// @brief pripravi 2d mapu pro tisk -> ohraniceni
    void BoardForPrintMake(int x_board, int y_board);
    /// @brief vybírání co provede počítač
    void AnalyseGameBot();

    // print metody
    ///tiskne mraveniste a info o nich dle majitele
    void printAnthillOwner(int owner);
    /// @brief vybírání jaký tah se provede
    char printChoiceOfMove();
    /// @brief vybírání mraveniste odkud se zautoci 
    /// @return vraci se id
    int printChoiceAnthillFrom();

public:
    Board();
    /// @brief nahraje mapu ze souboru
    /// @param name_of_map název mapy kterou si hrác vybral ve tride Game
    /// @return pokud se něco pokazi vrátí se false
    bool loadMap(string name_of_map); // nahraje mapu
    ///polozi mraveniste do 2d mapy
    void placeAntHill();                                                                                    // položi mraveniste kde ma byt
    ///kontrola jestli někdo již nevyhral
    bool checkWin();

    // print metody
    ///tisk herní plochy
    void printBoard(); // tisk herní plochy
    ///tisk info o mravenistich
    void status();
    /// @brief spracovava výběr tahu hráče
    /// @return vrátí 0 při nějaké chybě
    int printMove(); // tisk výběru tahu

    ///getter
    vector<AntHill> getAntHill_on_board();
    /// @brief nastavy vektor mravenist na novy -> pouzivani pri nacitani mapy
    /// @param new_AntsHill novy vektor mravenist
    /// @return pokud nejsou stejne velky vrati se false
    bool setAntHill_on_board(vector<AntHill> &new_AntsHill);
};

#endif // BOARD_H