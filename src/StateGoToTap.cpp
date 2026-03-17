#include "StateGoToTap.h"
#include "Context.h"
#include "StateTap.h"
#include "Robot.h"

StateGoToTap::StateGoToTap(int distance)
{
    flag = 0;
    distanceToTap = distance;
    ctx_->robot_->indicatorLED(0x1F);
}

void StateGoToTap::enter()
{
    ctx_->robot_->resetDistance();
    ctx_->robot_->writeMotors(-150, -150);
}
void StateGoToTap::update()
{
    switch (flag)
    {
    case 0:
        if (ctx_->robot_->getDistance() > distance)
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(0, 150);
            flag++;
        }
        break;
    case 1:
        if (ctx_->robot_->getAngle() > angle)
        {
            ctx_->robot_->lineFollow();
            flag++;
        }
        break;
    case 2:
        if (ctx_->robot_->getDistance() > distanceToTap)
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(150, 0);
            flag++;
        }
        break;
    case 3:
        if (ctx_->robot_->getAngle() > angle)
        {
            ctx_->robot_->lineFollow();
            flag++;
        }
        break;
    case 4:
        if (ctx_->robot_->getDistance() > distanceToTap)
            ctx_->transitionTo(new StateTap);
        break;
    }
}
void StateGoToTap::exit()
{
}