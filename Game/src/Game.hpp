#ifndef GAME_H
#define GAME_H

#include <string>
#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <algorithm>

#include "Board.hpp"

using namespace std;

class Game
{
private:
    // Interní proměnné pro reprezentaci stavu hry
    string MapSelect(); //vyber mapy
    string map; // číslo mapy 
public:
    Game();
    bool start(); //pusti hru -> vyběr mapy -> vyběr obtížnosti
    void player(); //tah hrace
    void bot(); //tah hrace

    void saveGame(const string saveFile); //ulozi hru
    void loadGame(const string saveFile); //nahraje hru
};

#endif // GAME_H