#ifndef BOT_H
#define BOT_H

#include"AntHill.hpp"

class Bot
{
private:
public:

    int max_utok = 0;
    bool nakup = false;
    bool utok = false;
    int pauza_kolo = 0;
    int money = 0;
    Bot();
};

#endif // BOT_H