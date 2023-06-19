#ifndef OBJECTONBOARD_H
#define OBJECTONBOARD_H

#include <memory>
/// @brief virtální metoda pro objekty na mapě
class ObjectOnBoard {
private:
    // Vlastnosti 
public:
    /// tisk polymorfních objektů který jsou na mapě
    virtual void print() = 0; 
    /// kontrola průchodnosti objektů
    virtual bool IsPassable() const = 0; 
    ///nastavení pruchodnosti objektu
    virtual void setPassable(bool pruchod) = 0; 

};

#endif  // OBJECTONBOARD_H
