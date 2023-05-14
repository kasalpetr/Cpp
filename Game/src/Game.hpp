#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.hpp"

class Game
{
private:
    // Interní proměnné pro reprezentaci stavu hry

public:
    Game();
    void start(); //pusti hru
    void saveGame(const string &saveFile); //ulozi hru
    void loadGame(const string &saveFile); //nahraje hru
};

#endif // GAME_H