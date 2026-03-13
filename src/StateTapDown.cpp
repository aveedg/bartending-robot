#include "StateTapDown.h"
#include "Context.h"
#include "StateTapUp.h"

void StateTapDown::enter()
{
}
void StateTapDown::update()
{
    // check if top LED array is on
    ctx_->transitionTo(new StateTapUp);
}
void StateTapDown::exit()
{
}