#ifndef GAME_H
#define GAME_H

#include <string>
#include "Board.hpp"

class Game {
private:
    // Interní proměnné pro reprezentaci stavu hry

public:
    void start();
    void saveGame(const std::string& saveFile);
    void loadGame(const std::string& saveFile);
};

#endif  // GAME_H