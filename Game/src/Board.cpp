#include "Board.hpp"

Board::Board()
{
}

Board::Board(vector<AntHill> antHills, vector<Obstacles> obstacles)
    : AntsHill_onBoard(antHills), Obstacles_onBoard(obstacles)
{
}

void Board::loadMap(string name_of_map)
{
    string Maps = "../examples/";
    string File_Name = Maps + name_of_map;
    ifstream file(File_Name);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            // Zde můžete provádět operace s řádkem
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cout << "Nepodařilo se otevřít soubor." << endl;
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
}