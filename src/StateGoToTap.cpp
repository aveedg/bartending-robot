#include "StateGoToTap.h"
#include "Context.h"
#include "StateTapDown.h"
#include "Robot.h"

int distanceToTap = 5; // mm
int flag = 0;
int angle = 90;

StateGoToTap::StateGoToTap(int distance)
{
    distance_ = distance;
}

void StateGoToTap::enter()
{
}
void StateGoToTap::update()
{
    ctx_->robot_->resetDistance();
    switch (flag)
    {
    case 0:
        if (ctx_->robot_->getDistance() < distance_)
            ctx_->robot_->lineFollow();
        else
            flag++;
        break;
    case 1:
        if (ctx_->robot_->getAngle() < angle)
            ctx_->robot_->pivotLeft();
        else
            flag++;
        break;

    case 2:
        if (ctx_->robot_->getDistance() < distanceToTap)
            ctx_->robot_->lineFollow();
        else
            ctx_->transitionTo(new StateTapDown);
        break;
    }
}
void StateGoToTap::exit()
{
}