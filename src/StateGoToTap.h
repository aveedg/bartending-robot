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
    int distance_;
};

#endif