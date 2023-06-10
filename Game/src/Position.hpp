#ifndef POSITION_H
#define POSITION_H

//pomocna trida pro lepsi pozicovani na herni mape
class Position {
private:
    int x;
    int y;

public:
    Position();
    Position(int x, int y);
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator<(const Position& other) const;
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
};

#endif  // POSITION_H