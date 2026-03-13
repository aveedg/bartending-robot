#ifndef CONTEXT_H
#define CONTEXT_H

class State;
class Robot;

class Context
{
private:
    State *currstate_;
    unsigned long startTime;
    bool timerActive;

public:
    Robot *robot_;
    Context(State *, Robot *); // constructor, says what to do when class is created
    ~Context() = default;      // destructor, says what to do when class is deleted

    void transitionTo(State *);
    void update(void);
    void startTimer(void);
};

#endif