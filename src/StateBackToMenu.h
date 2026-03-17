#ifndef STATEBACKTOMENU_H
#define STATEBACKTOMENU_H

#include "State.h"

class StateBackToMenu : public State
{
private:
    int flag = 0;
    float angle = 90;
    float distance = 5;
    float distance1 = 10;
    float distance2 = 5;

public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif