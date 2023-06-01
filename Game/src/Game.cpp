#include "Game.hpp"



Game::Game()
{
// Inicializace interních proměnných hry
}

void Game::start()
{
    cout <<  "random extra a" << endl;
        if (system("clear") != 0)
    {
        logic_error("chyba při přemazání terminálu");
    }
    cout <<  "Zatím jedeme bomby co :D " << endl;

}

void Game::player()
{
// Implementace tahu hráče
}

void Game::bot()
{
// Implementace tahu počítačového hráče (bota)
}

void Game::saveGame(const string saveFile)
{
// Implementace uložení hry do souboru
}

void Game::loadGame(const string saveFile)
{
// Implementace načtení hry ze souboru
}
