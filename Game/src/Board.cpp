#include "Board.hpp"
#include <sstream>

Board::Board() {}

Board::Board(vector<AntHill> antHills, vector<Obstacles> obstacles)
    : AntsHill_onBoard(antHills), Obstacles_onBoard(obstacles) {}

void Board::loadMap(string name_of_map) // nacteni mapy -> vybrani velikost hriste a pozice barier + pozice mravenistw
{
    x_board = 0;
    y_board = 0;
    string Maps = "../examples/";
    string File_Name = Maps + name_of_map; // cesta ke složce + nazev vybrane mapy
    ifstream file(File_Name);              // otevreni souboru
    if (file.is_open())
    {
        string line;
        while (getline(file, line)) // prochazi vsechny radky
        {
            if (line.find("x: ") == 0) // najde hodnotu x
            {
                Board::x_board = stoi(line.substr(3));
            }
            else if (line.find("y: ") == 0) // najde hodnotu y
            {
                Board::y_board = stoi(line.substr(3));
            }
            else if (line.find("anthills:") != string::npos) // našlo to anthills
            {
                int id = 0; // Inkrementace ID před cyklem while
                int x = 0;
                int y = 0;
                while (getline(file, line) && line.find("-") != string::npos)
                {
                    getline(file, line); // Načtení řádku s "x:"
                    try
                    {
                         x = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const std::invalid_argument &e)
                    {
                        continue;
                    }

                    getline(file, line); // Načtení řádku s "y:"
                    try
                    {
                         y = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const std::invalid_argument &e)
                    {
                        continue;
                    }

                    if ((x < x_board - 1 && x > 1) || (y < y_board - 1 && y > 1))
                    {
                        AntsHill_onBoard.push_back(AntHill(id, x, y)); // dám mraveniste do vektoru
                        id++;                                          // Inkrementace ID pro další mraveniště
                    }
                }
            }
        }
        file.close();
        system("clear");
    }
    else
    {
        cout << "Nepodařilo se otevřít soubor." << endl;
    }

    if (x_board == 0 || y_board == 0) // kontrola že je zadane x a y
    {
        cout << "Spatný konfiguracni soubor nektere hodnoty byly dodany automaticky\n"
             << endl;
        x_board = 100;
        y_board = 25;
    }
}
void Board::placeAntHill(AntHill *antHill, const Position &position)
{
    // implementace umístění mraveniště na desku
}

void Board::placeObstacles(Obstacles *obstacles, const Position &position)
{
    // implementace umístění překážek na desku
}

void Board::moveAnt(Ant *ant, const Position &newPosition)
{
    // implementace pohybu mravence na desce
}

void Board::removeAnt(Ant *ant)
{
    // implementace odstranění mravence z desky
}

void Board::printBoard()
{
    for (int row = 0; row < y_board; row++)
    {
        for (int col = 0; col < x_board; col++)
        {
            if (row == 0 || row == y_board - 1 || col == 0 || col == x_board - 1)
            {
                cout << "\033[1;31m#\033[0m";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }

    for (AntHill &anthill : AntsHill_onBoard)
    {
        cout << "id:" << anthill.id << " X:" << anthill.position.getX() << " Y:" << anthill.position.getY() << endl;
    }
}