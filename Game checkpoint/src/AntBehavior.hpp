#ifndef ANTBEHAVIOR_H
#define ANTBEHAVIOR_H

#include "AntBehaviorABS.hpp"

class AntBehaviorAttack : public AntBehaviorABS {
private:
    //typ mravence(utok)
public:
    void ApplyType() override;
};



class AntBehaviorDefend : public AntBehaviorABS {
private:
    //typ mravence(obrana)
public:
    void ApplyType() override;
};

class AntBehaviorQuick : public AntBehaviorABS {
private:
    //typ mravence(rychly)
public:
    void ApplyType() override;
};

#endif  // ANTBEHAVIOR_H
