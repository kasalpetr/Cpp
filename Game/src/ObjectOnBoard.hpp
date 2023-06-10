#ifndef OBJECTONBOARD_H
#define OBJECTONBOARD_H

#include <memory>

class ObjectOnBoard {
private:
    // Vlastnosti 
public:
    virtual void print() = 0; //
    virtual bool IsPassable() const = 0; //
    virtual void setPassable(bool pruchod) = 0;

};

#endif  // OBJECTONBOARD_H
