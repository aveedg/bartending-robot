#include "StateTapUp.h"
#include "Context.h"
#include "StateBackToMenu.h"
#include "Robot.h"
#include "StateReadMenu.h"

int flag = 0;
float angle = 90;
float distance = 5;
float distance1 = 10;
float distance2 = 5;

void StateBackToMenu::enter()
{
}
void StateBackToMenu::update()
{
    switch (flag)
    {
    case 0:
        if (ctx_->robot_->getDistance() < distance)
            ctx_->robot_->backwardLineFollow();
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
        if (ctx_->robot_->getDistance() < distance1)
            ctx_->robot_->lineFollow();
        else
            flag++;
        break;

    case 3:
        if (ctx_->robot_->getAngle() < angle)
            ctx_->robot_->pivotRight();
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
