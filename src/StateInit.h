#ifndef STATEINIT_H
#define STATEINIT_H

#include "State.h"

class StateInit : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif