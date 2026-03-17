#include <Arduino.h>
#include "StateMaze.h"
#include "Context.h"
#include "StateGoToMenu.h"
#include "Robot.h"
#include "StateReadMenu.h"

void StateMaze::enter()
{
    flag = 0;
    Serial.println("State: MAZE");
    ctx_->robot_->indicatorLED(0x03);
}
void StateMaze::update()
{
    switch (flag)
    {
    case 0:
        if (ctx_->robot_->lineLost())
        {
            ctx_->robot_->writeMotors(100, 150); // might have to change values
            flag++;
        }
        else
        {
            ctx_->robot_->lineFollow();
        }
        break;

    case 1:
        if (!ctx_->robot_->lineLost())
        {
            flag++;
        }
        break;

    case 2:
        if (ctx_->robot_->lineLost())
        {
            ctx_->robot_->writeMotors(150, 100);
            flag++;
        }
        else
        {
            ctx_->robot_->lineFollow();
        }
        break;

    case 3:
        if (!ctx_->robot_->lineLost())
        {
            flag++;
        }
        break;

    case 4:
        if (ctx_->robot_->clockIn())
        {
            ctx_->transitionTo(new StateReadMenu);
            return;
        }
        else
        {
            ctx_->robot_->lineFollow();
            // if (ctx_->robot_->senseLineRight())
            // {
            //     ctx_->robot_->resetDistance();
            //     if (ctx_->robot_->getDistance() < 20)
            //     {
            //         ctx_->robot_->writeMotors(150, 150);
            //     }
            //     else
            //     {
            //         ctx_->robot_->lineFollow();
            //     }
            // }
        }
        break;

    default:
        ctx_->robot_->lineFollow();
        break;
    }
}

void StateMaze::exit()
{
    // start timer
    ctx_->startTimer();
}
