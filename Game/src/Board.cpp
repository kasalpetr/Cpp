#include "Board.hpp"

Board::Board()
{}

Board::Board(vector<AntHill*> antHills, vector<Obstacles*> obstacles)
    : AntsHill_onBoard(antHills), Obstacles_onBoard(obstacles)
{}

void Board::loadMap(const string& mapFile)
{
    // implementace načítání mapy
}

void Board::placeAntHill(AntHill* antHill, const Position& position)
{
    // implementace umístění mraveniště na desku
}

void Board::placeObstacles(Obstacles* obstacles, const Position& position)
{
    // implementace umístění překážek na desku
}

void Board::moveAnt(Ant* ant, const Position& newPosition)
{
    // implementace pohybu mravence na desce
}

void Board::removeAnt(Ant* ant)
{
    // implementace odstranění mravence z desky
}

void Board::printBoard()
{

}