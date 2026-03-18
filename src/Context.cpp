#include "Context.h"
#include "State.h"
#include "StateSong.h"
#include <Arduino.h>

Context::Context(State *initialState, Robot *robot) : currstate_(nullptr), robot_(robot)
{ // constructor
    transitionTo(initialState);
}

void Context::transitionTo(State *state)
{
    if (currstate_ != nullptr)
    {
        currstate_->exit();
        delete currstate_;
    }
    currstate_ = state;
    currstate_->setContext(this);
    currstate_->enter();
}

void Context::startTimer()
{
    startTime = millis();
    timerActive = true;
}

void Context::update()
{
    if (currstate_ != nullptr)
    {
        currstate_->update();
    }

    // interrupt after 50 sec
    if (timerActive && (millis() - startTime >= 50000))
    {
        Serial.print("i am inside an if statement");
        timerActive = false;
        transitionTo(new StateSong);
    }
}
