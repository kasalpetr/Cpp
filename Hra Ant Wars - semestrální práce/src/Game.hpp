#ifndef GAME_H
#define GAME_H

#include <string>
#include <limits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>


#include "Board.hpp"

using namespace std;

/**
 * @mainpage Ant Wars
 *
 * Chtěl bych vám představit hru ant Wats. Tato hra je tahová, každý tah se vyhodnocuje jednotlivě.
 * O co jde v této hře -> porazit počítač a obsadit všechny mraveniště.
 * Zároveň se může stát že vás počítač porazí a vy tak prohrajete
 * Hra načítá mapy ze souboru, stejně tak uložené hry, pokud chcete pustit uloženou hru kterou jste hráli na mapě A musíte zároveň mít mapu A
 * zároveň se u každé mapy načítají ceny bonusu a prerekvizita k odemknutí 5 bonusu, počítač tuto prerekvizitu nepotřebuje zárvon ale tento bonus pocitac vyuzivá nejmene
 * Pote co se načte hra tak je hráč reprezentován zelenou barvou, počítač modrou, neutrální barva je červená
 * Hráč má možnosti útoku na mraveniště tak i podpory mraveništ a používání bonusu, v případě že hráč chce prát pasivně je zde možnost i odehrát kolo bez tahu.
 * Po útoku na mraveniště se zbylý mravenci přidají k obsazenému mraveništi a zabydlí se zde, pote co se zabydli dostanou výcvik i zdejšího mraveniště, tento výcvik vojáky může jak zhoršit tak vylepšit. V případě podpory je to se zabydlováním a výcvikem stejné. Hráč má možnost sledovat aktuální stav všech mravenišť počítače a hráče. Vidí kolik mají zrovna mravencu, maximální počet mravenců, id, level mraveniště a útok s obranou na který jsou cvičeni zdejší mravenci.
 * Přeji šťastnou hru
 *
 * 
 */

class Game /// Hlavní třída která zprostředkovává běh celé hry
{
private:
    // Interní proměnné pro reprezentaci stavu hry
    string MapSelect(string _directory); /// davá na výběr mapy a hráč si jednu zvolí
    string map; /// jméno mapy 
public:
    Game();
    bool start(); /// pusti hru -> vyběr mapy -> v případě dobrého načtení se hra rozběhne

    void saveGame(Board &b); //ulozi hru do souboru který je povolen pouze pro čtení -> není možné přepisovat savy
    void loadGame(); //nahraje hru a pote ji spustí pokud se vše povede
};

#endif // GAME_H