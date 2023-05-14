#ifndef POSITION_H
#define POSITION_H

//pomocna trida pro lepsi pozicovani na herni mape
class Position {
private:
    int x;
    int y;

public:
    Position(int x, int y);
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
};

#endif  // POSITION_H