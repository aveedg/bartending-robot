#ifndef STATEGOTOTAP_H
#define STATEGOTOTAP_H

#include "State.h"

class StateGoToTap : public State
{
public:
    StateGoToTap(int distance);
    void enter() override;
    void update() override;
    void exit() override;

private:
    int distance = 5;
    int flag = 0;
    float distanceToTap;
    float angle = 90.00;
};

#endif