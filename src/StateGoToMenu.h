#ifndef STATEGOTOMENU_H
#define STATEGOTOMENU_H

#include "State.h"

class StateGoToMenu : public State
{
private:
    int flag = 0;
    float angle = 90;
    float distance = 310;
    float distance1 = 110;

public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif