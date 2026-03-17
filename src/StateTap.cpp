#include "StateTap.h"
#include "Context.h"
#include "StateBackToMenu.h"
#include "Robot.h"

void StateTap::enter()
{
    ctx_->robot_->indicatorLED(0x3F);
    ctx_->robot_->tapDown();
}
void StateTap::update()
{
    if (ctx_->robot_->beerFull())
    {
        ctx_->robot_->tapUp();
        ctx_->transitionTo(new StateBackToMenu);
    }
}
void StateTap::exit()
{
}