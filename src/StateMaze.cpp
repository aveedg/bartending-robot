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
    ctx_->robot_->initLineFollow();
}
void StateMaze::update()
{
    switch (flag)
    {
    case 0:
        Serial.println("case 0");
        ctx_->robot_->indicatorLED(0x01);
        ctx_->robot_->resetDistance();
        if (ctx_->robot_->lineLost())
        {
            ctx_->robot_->resetDistance();
            flag++;
            break;
        }
        else
        {
            Serial.print("running");
            ctx_->robot_->lineFollow();
        }
        break;

    case 1:
        if (ctx_->robot_->getDistance() > 300)
        {
            Serial.print("turn1");
            ctx_->robot_->writeMotors(38, 150); // 150, 33
        }
        else if (!(ctx_->robot_->lineLost()))
        {
            ctx_->robot_->initLineFollow();
            ctx_->robot_->lineFollow();
            flag++;
            break;
        }
        else
        {
            Serial.print("turn2");
            ctx_->robot_->writeMotors(0, 150);
        }
        // case 2:
        //     Serial.println("case 1");
        //     ctx_->robot_->indicatorLED(0x02);
        //     if (!(ctx_->robot_->lineLost()))
        //     {
        //         ctx_->robot_->initLineFollow();
        //         ctx_->robot_->lineFollow();
        //         flag++;
        //     }
        //     break;

    case 2:
        Serial.println("case 2");
        ctx_->robot_->indicatorLED(0x03);
        if (ctx_->robot_->lineLost())
        {
            ctx_->robot_->resetDistance();
            if (ctx_->robot_->getDistance() > 10)
            {
                ctx_->robot_->writeMotors(150, 38); // 150, 33
            }
            else
            {
                Serial.print("turn2");
                ctx_->robot_->writeMotors(150, 0);
                flag++;
            }
            break;
        }
        else
        {
            Serial.println("running");
            ctx_->robot_->lineFollow();
        }
        break;

    case 3:
        Serial.println("case 3");
        ctx_->robot_->indicatorLED(0x04);
        if (!ctx_->robot_->lineLost())
        {
            ctx_->robot_->initLineFollow();
            ctx_->robot_->lineFollow();
            flag++;
        }
        break;

    case 4:
        Serial.println("case 4");
        ctx_->robot_->indicatorLED(0x05);
        if (ctx_->robot_->clockIn())
        {
            ctx_->transitionTo(new StateReadMenu);
            return;
            break;
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
    }
}

void StateMaze::exit()
{
    // start timer
    ctx_->startTimer();
}
