#ifndef GAME_H
#define GAME_H

#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>


#include "Board.hpp"

using namespace std;

class Game
{
private:
    // Interní proměnné pro reprezentaci stavu hry
    string MapSelect(string _directory); //vyber mapy
    string map; // číslo mapy 
public:
    Game();
    bool start(); //pusti hru -> vyběr mapy -> vyběr obtížnosti

    void saveGame(Board &b); //ulozi hru
    void loadGame(); //nahraje hru
};

#endif // GAME_H