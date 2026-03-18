#include "StateReadMenu.h"
#include "Context.h"
#include "Robot.h"
#include "StateGoToTap.h"
#include <Arduino.h>

void StateReadMenu::enter()
{
    analogReference(DEFAULT);
    ctx_->robot_->indicatorLED(0x15);
}
void StateReadMenu::update()
{
    // maybe move to exit of last state?
    int closestColor = ctx_->robot_->readColor();

    if (closestColor == 1)
    {
        Serial.print("yellow");
        ctx_->robot_->indicatorLED(0x01); // yellow
        float distance = 135;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 2)
    {
        Serial.print("blue");
        ctx_->robot_->indicatorLED(0x02); // blue
        float distance = 330;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 3)
    {
        Serial.print("red");
        ctx_->robot_->indicatorLED(0x03); // red
        float distance = 530;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 4)
    {
        Serial.print("green");
        ctx_->robot_->indicatorLED(0x04); // green
        float distance = 735;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
}
void StateReadMenu::exit()
{
}
