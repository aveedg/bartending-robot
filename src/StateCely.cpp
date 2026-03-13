#include "StateCely.h"
#include "Context.h"
#include "StateReadMenu.h"

void StateCely::enter()
{
    // start timer
    ctx_->startTimer();
    ctx_->transitionTo(new StateReadMenu);
}
void StateCely::update()
{
}
void StateCely::exit()
{
}