#ifndef STATE_H
#define STATE_H

class Context;

class State
{
protected:
    Context *ctx_; // underscore after is member something.....

public:
    virtual ~State() = default;

    void setContext(Context *);

    virtual void enter() = 0; // virtual means children will override these functions
    virtual void update() = 0;
    virtual void exit() = 0;
};

#endif