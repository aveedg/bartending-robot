#ifndef STATEMAZE_H
#define STATEMAZE_H

#include "State.h"

class StateMaze : public State
{
private:
    int flag;

public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif