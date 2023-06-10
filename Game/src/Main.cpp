#include "Game.hpp"
#include <limits>
#include <csignal>

int main(int argc, char const *argv[])
{
    system("clear");
    Game game;
    int option;

    while (true) // pusteni hry 3 moznosti -> Nová hra, načíst hru, Ukončit hru
    {
        /* code */

        std::cout << "Vyberte moznost:\n";
        std::cout << "1. Spustit hru\n";
        std::cout << "2. Načíst hru\n";
        std::cout << "3. Ukončit hru\n";

        // Čtení vstupu od uživatele
        if (!(std::cin >> option))
        {
            if (std::cin.eof())
            {
                exit(1);
            }

            system("clear");
            std::cout << "Neplatny vstup. Zadejte platnou volbu.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        // Zpracování volby
        switch (option)
        {
        case 1:
            // Provádění akce pro možnost 1
            system("clear");
            game.start();
            return 0;
        case 2:
            // Provádění akce pro možnost 2
            system("clear");
            std::cout << "Načíst hru\n";
            return 0;
        case 3:
            // Provádění akce pro možnost 3
            system("clear");
            return 0;
        default:
            system("clear");
            std::cout << "Neplatny vstup. Zadejte platnou volbu.\n";
            break;
        }
    }
    return 0;
}
