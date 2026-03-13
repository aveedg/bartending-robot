#ifndef STATESONG_H
#define STATESONG_H

#include "State.h"

class StateSong : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif