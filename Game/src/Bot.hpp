#ifndef BOT_H
#define BOT_H

class Bot
{
private:
    // privatní metody pro zjistený optimálního tahu pro počítač
    void findMove();

public:
    Bot();
    void Move(); //provedeni tahu
};

#endif // BOT_H