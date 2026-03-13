#ifndef STATEREADMENU_H
#define STATEREADMENU_H

#include "State.h"

class StateReadMenu : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif