#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.hpp"
#include "Bot.hpp"

class Game
{
private:
    // Interní proměnné pro reprezentaci stavu hry
    
public:
    Game();
    void start(); //pusti hru
    void player(); //tah hrace
    void bot(); //tah hrace
    void saveGame(const string &saveFile); //ulozi hru
    void loadGame(const string &saveFile); //nahraje hru
};

#endif // GAME_H