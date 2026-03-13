#ifndef STATEGOTOMENU_H
#define STATEGOTOMENU_H

#include "State.h"

class StateGoToMenu : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif