#ifndef STATETAPUP_H
#define STATETAPUP_H

#include "State.h"

class StateTapUp : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif