#include "StateGoToMenu.h"
#include "Context.h"
#include "StateReadMenu.h"
#include "Robot.h"

int flag = 0;
float angle = 90;
float distance = 5;
float distance1 = 10;
float distance2 = 5;

void StateGoToMenu::enter()
{
}
void StateGoToMenu::update()
{
    ctx_->robot_->resetDistance();

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
            ctx_->robot_->pivotRight();
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
            ctx_->robot_->pivotLeft();
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
}
void StateGoToMenu::exit()
{
}