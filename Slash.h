#ifndef SLASH_H
#define SLASH_H

#include "Game_Stat.h"
#include "BObject.h"

class Slash : public BaseObject
{
public:
    Slash();
    ~Slash();

    void set_attack (bool check) {is_attack = check;};

private:
    bool is_attack;
};

#endif // SLASH_H
