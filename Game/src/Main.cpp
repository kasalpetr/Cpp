#include "Game.hpp"
#include <limits>


int main(int argc, char const *argv[])
{
    Game game;
    int option;

    while (true)
    {
        /* code */

        std::cout << "Vyberte moznost:\n";
        std::cout << "1. Spustit hru\n";
        std::cout << "2. Načíst hru\n";
        std::cout << "3. Ukončit hru\n";

        // Čtení vstupu od uživatele
        if (!(std::cin >> option))
        {
            std::cout << "Neplatny vstup. Zadejte platnou volbu.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Zpracování volby
        switch (option)
        {
        case 1:
            game.start();
            // Provádění akce pro možnost 1
            return 0;
        case 2:
            std::cout << "Načíst hru\n";
            // Provádění akce pro možnost 2
            return 0;
        case 3:
            // Provádění akce pro možnost 3
            return 0;
        default:
            std::cout << "Neplatny vstup. Zadejte platnou volbu.\n";
            break;
        }
    }
    return 0;
}
