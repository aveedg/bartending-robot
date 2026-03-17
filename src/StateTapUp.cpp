#include "StateTapUp.h"
#include "Context.h"
#include "StateBackToMenu.h"
#include "Robot.h"

void StateTapUp::enter()
{
    ctx_->robot_->releaseString();
    ctx_->robot_->openClaw();
}
void StateTapUp::update()
{
    ctx_->robot_->checkFull();
    ctx_->robot_->moveArm();
    ctx_->transitionTo(new StateBackToMenu);
}
void StateTapUp::exit()
{
}