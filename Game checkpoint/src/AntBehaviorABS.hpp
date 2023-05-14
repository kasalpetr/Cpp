#ifndef ANTBEHAVIORABS_H
#define ANTBEHAVIORABS_H

class AntBehaviorABS {
private:
    // Vlastnosti bonusového efektu

public:
    AntBehaviorABS();
    virtual void ApplyType() = 0; // prirazeni typu k mravenci
};

#endif  // ANTBEHAVIORABS_H
