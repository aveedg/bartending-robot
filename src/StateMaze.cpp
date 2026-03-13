#include <Arduino.h>
#include "StateMaze.h"
#include "Context.h"
#include "StateGoToMenu.h"
#include "Robot.h"

int flag = 0;

void StateMaze::enter()
{
}
void StateMaze::update()
{

    if (flag == 0 && ctx_->robot_->lineLost())
    {
        ctx_->robot_->spinLeft();
        flag++;
    }
    else if (flag == 1 && !(ctx_->robot_->lineLost()))
    {
        ctx_->robot_->lineFollow();
    }
    else if (flag == 1 && ctx_->robot_->lineLost())
    {
        ctx_->robot_->spinRight();
        flag++;
    }
    else if (flag == 2 && !(ctx_->robot_->lineLost()))
    {
        ctx_->robot_->lineFollow();
    }
    else if (ctx_->robot_->clockIn())
    {
        ctx_->transitionTo(new StateGoToMenu);
    }
    else
    {
        ctx_->robot_->lineFollow();
    }
}

void StateMaze::exit()
{
}
