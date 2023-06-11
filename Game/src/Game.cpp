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

    if (directory == "../examples/")
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
    if (directory == "../examples/")
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
            if (directory == "../examples/")
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
    int stav = -1;
    Board Board;
    map = MapSelect("../examples/"); // do promene map se uloží číslo mapy
    if (std::cin.eof())
        return false;
    Board.loadMap(map); // načte se mapa do souboru
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
    return true;
}

void Game::saveGame(Board &b)
{
    string Savename;
    string directory = "../examples/save/";
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
        std::cout << "Hra byla úspěšně uložena do souboru." << std::endl;
    }
    else
    {
        std::cout << "Nepodařilo se otevřít soubor pro uložení." << std::endl;
    }
}

void Game::loadGame()
{
    // Implementace načtení hry ze souboru
    string save;
    save = MapSelect("../examples/save");
}
