#ifndef STATETAP_H
#define STATETAP_H

#include "State.h"

class StateTap : public State
{
public:
    void enter() override;
    void update() override;
    void exit() override;
};

#endif