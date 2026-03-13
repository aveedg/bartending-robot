#ifndef STATECELY_H
#define STATECELY_H

#include "State.h"

class StateCely : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif