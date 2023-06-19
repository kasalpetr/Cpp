#include "Game.hpp"

Game::Game() {} // konstruktor

string Game::MapSelect(string _directory) // dotazování na vyber mapy
{
    string directory = _directory;
    vector<string> availableMaps;

    // Získání seznamu dostupných map
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(directory.c_str())) != nullptr)
    {
        while ((entry = readdir(dir)) != nullptr)
        {
            string filename = entry->d_name;
            if (filename.substr(filename.find_last_of(".") + 1) == "txt")
            {
                availableMaps.push_back(filename);
            }
        }
        closedir(dir);
    }

    if (directory == "examples/")
    {
        cout << "Dostupne mapy:" << endl;
    }
    else
    {
        cout << "Dostupne Savy:" << endl;
    }

    // Výpis dostupných map
    for (const string &mapName : availableMaps)
    {
        cout << mapName << endl;
    }
    cout << endl;
    // Zadání názvu mapy od uživatele
    string selectedMap;
    if (directory == "examples/")
    {
        cout << "Zadejte nazev mapy: ";
    }
    else
    {
        cout << "Zadejte nazev Savu: ";
    }

    cin >> selectedMap;

    // Kontrola, zda zadaný název mapy existuje
    bool validMap = false;
    while (!validMap)
    {
        validMap = find_if(availableMaps.begin(), availableMaps.end(), [&selectedMap](const string &map)
                           { return map.compare(selectedMap) == 0; }) != availableMaps.end();

        if (!validMap)
        {
            if (directory == "examples/")
            {
                cout << "Zadany nazev mapy neexistuje. Zadejte platny nazev: ";
            }
            else
            {
                cout << "Zadany nazev savu neexistuje. Zadejte platny nazev: ";
            }
            if (std::cin.eof())
                return "random";
            cin >> selectedMap;
        }
    }
    return selectedMap;
}

bool Game::start()
{
    bool fail_load_map = true; // true když je to ok
    int stav = -1;
    Board Board;
    map = MapSelect("examples/"); // do promene map se uloží číslo mapy
    if (std::cin.eof())
        return false;
    fail_load_map = Board.loadMap(map); // načte se mapa do souboru
    Board.placeAntHill();
    if (fail_load_map)
    {
        while (1)
        {
            Board.printBoard(); // vypise jak vypadá mapa
            Board.status();
            stav = Board.printMove();
            if (stav == 0)
            {
                break;
            }
            if (stav == 2)
            {
                system("clear");
                saveGame(Board);
                break;
            }
            if (Board.checkWin())
            {
                break;
            }
        }
    }else
    {
        cout << "Nepodarilo se nacist mapu" << endl;
    }
    
    return true;
}

void Game::saveGame(Board &b)
{
    string Savename;
    string directory = "examples/save/";
    cout << "Napiš název souboru do kterého chceš uložit tuto hru" << endl;
    cin >> Savename;
    directory = directory + Savename + ".txt";
    std::ofstream file(directory);

    if (file.is_open())
    {
        std::vector<AntHill> AntHills = b.getAntHill_on_board();
        file << map << std::endl;
        for (const auto &anthills : AntHills)
        {
            file << anthills.getId() << ", " << anthills.getlevel() << ", " << anthills.getNumberOfAnts() << ", " << anthills.getMaxNumberOfAnts() << ", " << anthills.getOwner() << ", " << anthills.getAttack() << ", " << anthills.getDefend() << endl;
        }

        file.close();
        // Set file permissions to read for all users
        if (chmod(directory.c_str(), S_IRUSR | S_IRGRP | S_IROTH) != 0)
        {
            std::cout << "Nepodařilo se nastavit práva ke čtení pro soubor." << std::endl;
        }
        else
        {
            std::cout << "Hra byla úspěšně uložena do souboru." << std::endl;
        }
    }
    else
    {
        std::cout << "Nepodařilo se otevřít soubor pro uložení." << std::endl;
        saveGame(b);
    }
}

void Game::loadGame()
{
    bool fail_load_map = true;
    int stav = -1;
    bool error = false;
    vector<AntHill> load_AntHill;
    vector<int> antHillData;
    Board Board;
    // Implementace načtení hry ze souboru
    string directory = "examples/save/";
    string save;
    save = MapSelect("examples/save");
    directory = directory + save;
    ifstream file(directory);

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line); // Načtení prvního řádku (název mapy)
        std::string map = line;
        while (std::getline(file, line))
        {
            std::istringstream iss(line);
            std::string token;
            antHillData.clear();

            while (std::getline(iss, token, ','))
            {
                int value = std::stoi(token);
                antHillData.push_back(value);
            }
            // Vytvoření mraveniště a předání hodnot
            AntHill anthill;
            anthill.loadnewAntHills(antHillData[0], antHillData[1], antHillData[2], antHillData[3], antHillData[4], antHillData[5], antHillData[6]);
            load_AntHill.push_back(anthill);
            // Přidání mraveniště na desku
        }
        fail_load_map = Board.loadMap(map);
        Board.setAntHill_on_board(load_AntHill);
        Board.placeAntHill();
        file.close();
        if (!fail_load_map)
        {
            error = true;
        }

        std::cout << "Hra byla úspěšně načtena." << std::endl;
        // Nastavení načtené mapy
    }
    else
    {
        std::cout << "Nepodařilo se otevřít soubor pro načtení." << std::endl;
        error = true;
    }
    if (!error)
    {
        /* code */

        while (1)
        {
            Board.printBoard(); // vypise jak vypadá mapa
            Board.status();
            stav = Board.printMove();
            if (stav == 0)
            {
                break;
            }
            if (stav == 2)
            {
                system("clear");
                saveGame(Board);
                break;
            }
            if (Board.checkWin())
            {
                break;
            }
        }
    }else
    {
        cout << "Nepodarilo se nacist mapu" << endl;
    }
    
}
