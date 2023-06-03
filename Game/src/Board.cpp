#include "Board.hpp"
#include <sstream>

Board::Board() {}

Board::Board(vector<AntHill> antHills, vector<Obstacles> obstacles)
    : AntsHill_onBoard(antHills), Obstacles_onBoard(obstacles) {}

void Board::placeAntHill()
{
    // implementace umístění mraveništ na desku
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        int x = anthill.getPosition().getX();
        int y = anthill.getPosition().getY();
        board_for_print[y][x] = make_unique<AntHill>(anthill);
    }
}

void Board::placeObstacles(int x, int y)
{
    // Implementace umístění překážek na desku
    board_for_print[y][x] = make_unique<Obstacles>();
}

bool Board::checkplace(vector<AntHill> &AntsHill_onBoard, vector<Obstacles> &Obstacles_onBoard, int x, int y)
{
    for (const AntHill &anthill : AntsHill_onBoard)
    {
        if (!checkAroundPlace(anthill.getPosition().getX(), anthill.getPosition().getY(), x, y))
        {
            return false; // Duplicitní mraveniště
        }
    }
    return true; // Žádné duplicitní mraveniště
}

bool Board::checkAroundPlace(int x, int y, int new_x, int new_y)
{
    if (abs(new_x - x) <= 1 && abs(new_y - y) <= 1)
    {
        return false; // New coordinates are touching or overlapping the old coordinates
    }
    return true;
}

void Board::BoardForPrintMake(int y_board, int x_board)
{
    board_for_print.resize(x_board);
    for (int row = 0; row < x_board; row++)
    {
        board_for_print[row].resize(y_board);
        for (int col = 0; col < y_board; col++)
        {
            if (row == 0 || row == x_board - 1 || col == 0 || col == y_board - 1)
            {
                board_for_print[row][col] = std::make_unique<Obstacles>();
            }
            else
            {
                board_for_print[row][col] = std::make_unique<EmptySpace>();
            }
        }
    }
}


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
        getline(file, line);
        line.find("x: "); // najde hodnotu x
        Board::x_board = stoi(line.substr(3));
        getline(file, line);
        line.find("y: "); // najde hodnotu y
        Board::y_board = stoi(line.substr(3));
        BoardForPrintMake(x_board, y_board);

        while (getline(file, line)) // prochazi vsechny radky
        {
            if (line.find("anthills:") != string::npos) // našlo to anthills
            {

                int id = 0; // Inkrementace ID před cyklem while
                int x = 0;
                int y = 0;
                while (getline(file, line) && line.find("-") != string::npos) // najde to pomlcku -> další mraveniste
                {

                    getline(file, line); // Načtení řádku s "x:"
                    try
                    {
                        x = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const invalid_argument &e)
                    {
                        continue;
                    }

                    getline(file, line); // Načtení řádku s "y:"
                    try
                    {
                        y = stoi(line.substr(line.find(":") + 1));
                    }
                    catch (const invalid_argument &e)
                    {
                        continue;
                    }

                    if (((x < x_board - 1 && x > 1) && (y < y_board - 1 && y > 1)) && checkplace(AntsHill_onBoard, Obstacles_onBoard, x, y))
                    {
                        AntHill new_Anthill(id, x, y);
                        AntsHill_onBoard.push_back(new_Anthill); // dám mraveniste do vektoru
                        id++;                                    // Inkrementace ID pro další mraveniště
                    }
                }
            }
            else if (line.find("obstacles:") != string::npos && line.substr(0, 10) == "obstacles:")
            {
                cout << "random" << endl;
                while (getline(file, line) && !line.empty())
                {
                    
                    // Rozdělení řádku podle čárky na souřadnice x a y
                    size_t commaPos = line.find(",");
                    if (commaPos != string::npos)
                    {
                        int x = stoi(line.substr(0, commaPos));
                        int y = stoi(line.substr(commaPos + 1));

                        // Přidání překážky do vektoru
                        if (((x < x_board - 1 && x > 1) && (y < y_board - 1 && y > 1)) && checkplace(AntsHill_onBoard, Obstacles_onBoard, x, y))
                        {
                            placeObstacles(x,y);
                        }
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

    placeAntHill();
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
    for (long unsigned int row = 0; row < board_for_print.size(); row++)
    {
        for (long unsigned int col = 0; col < board_for_print[row].size(); col++)
        {
            board_for_print[row][col]->print();
        }
        cout << endl;
    }
}