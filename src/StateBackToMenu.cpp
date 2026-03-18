#include "StateTap.h"
#include "Context.h"
#include "StateBackToMenu.h"
#include "Robot.h"
#include "StateReadMenu.h"

void StateBackToMenu::enter()
{
    ctx_->robot_->indicatorLED(0xFF);
}
void StateBackToMenu::update()
{
    switch (flag)
    {
    case 0:
        if (ctx_->robot_->getDistance() < distance)
            ctx_->robot_->writeMotors(-100, -100); // might not work because of wheel position
        else
            flag++;
        break;

    case 1:
        if (ctx_->robot_->getAngle() < angle)
            ctx_->robot_->writeMotors(150, 0); // turn left
        else
            flag++;
        break;

    case 2:
        if (ctx_->robot_->getDistance() < distance1)
            ctx_->robot_->lineFollow();
        else
            flag++;
        break;

    case 3:
        if (ctx_->robot_->getAngle() < angle)
            ctx_->robot_->writeMotors(0, 150); // turn right
        else
            flag++;
        break;

    case 4:
        if (ctx_->robot_->getDistance() < distance2)
            ctx_->robot_->lineFollow();
        else
            ctx_->transitionTo(new StateReadMenu);
        break;
    }
    ctx_->transitionTo(new StateReadMenu);
}

void StateBackToMenu::exit()
{
}
