#include "StateReadMenu.h"
#include "Context.h"
#include "Robot.h"
#include "StateGoToTap.h"
#include <Arduino.h>

void StateReadMenu::enter()
{
    analogReference(DEFAULT);
}
void StateReadMenu::update()
{
    int closestColor = ctx_->robot_->readColor();

    if (closestColor == 1)
    {
        ctx_->robot_->indicatorLED(0x01);
        float distance = 4.5;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 2)
    {
        ctx_->robot_->indicatorLED(0x02);
        float distance = 8.5;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 3)
    {
        ctx_->robot_->indicatorLED(0x03);
        float distance = 12.5;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
    else if (closestColor == 4)
    {
        ctx_->robot_->indicatorLED(0x04);
        float distance = 16.5;
        ctx_->transitionTo(new StateGoToTap(distance));
    }
}
void StateReadMenu::exit()
{
}
