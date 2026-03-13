#ifndef STATEBACKTOMENU_H
#define STATEBACKTOMENU_H

#include "State.h"

class StateBackToMenu : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif