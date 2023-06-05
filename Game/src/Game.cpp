#include "Game.hpp"


Game::Game(){} //konstruktor

string Game::MapSelect() // dotazování na vyber mapy
{
    string directory = "../examples/";
    vector<string> availableMaps;

    // Získání seznamu dostupných map
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(directory.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr) {
            string filename = entry->d_name;
            if (filename.substr(filename.find_last_of(".") + 1) == "txt") {
                availableMaps.push_back(filename);
            }
        }
        closedir(dir);
    }

    // Výpis dostupných map
    cout << "Dostupne mapy:" << endl;
    for (const string& mapName : availableMaps) {
        cout << mapName << endl;
    }
    cout << endl;
      // Zadání názvu mapy od uživatele
    string selectedMap;
    cout << "Zadejte nazev mapy: ";
    cin >> selectedMap;

    // Kontrola, zda zadaný název mapy existuje
    bool validMap = false;
    while (!validMap) {
        validMap = find_if(availableMaps.begin(), availableMaps.end(), [&selectedMap](const string& map) {
            return map.compare(selectedMap) == 0;
        }) != availableMaps.end();

        if (!validMap) {
            cout << "Zadany nazev mapy neexistuje. Zadejte platny nazev: ";
            cin >> selectedMap;
        }
    }
    return selectedMap;
}

void Game::start()
{
Board Board;
map = MapSelect(); //do promene map se uloží číslo mapy
Board.loadMap(map); //načte se mapa do souboru
while (1)
{
Board.printBoard(); // vypise jak vypadá mapa
Board.printAnthills();
Board.printMove();
Board.MakeMove();
if (Board.checkWin())
{
    break;
}
}
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
