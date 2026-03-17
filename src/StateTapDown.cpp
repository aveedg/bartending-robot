#include "StateTapDown.h"
#include "Context.h"
#include "StateTapUp.h"

void StateTapDown::enter()
{
    ctx_->robot_->closeClaw();
    ctx_->robot_->pullString();
}
void StateTapDown::update()
{
    // check if top LED array is on
    ctx_->transitionTo(new StateTapUp);
}
void StateTapDown::exit()
{
}