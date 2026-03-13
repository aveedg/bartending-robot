#ifndef STATETAPDOWN_H
#define STATETAPDOWN_H

#include "State.h"

class StateTapDown : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif