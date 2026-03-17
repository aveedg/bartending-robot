#include "StateInit.h"
#include "Context.h"
#include "StateMaze.h"
#include "Robot.h"
#include <QTRSensors.h>
#include <Arduino.h>

void StateInit::enter()
{
    Serial.println("State: INIT");
    ctx_->robot_->indicatorLED(0x01);

    ctx_->robot_->calibrate();
    ctx_->transitionTo(new StateMaze);
}
void StateInit::update()
{
}
void StateInit::exit()
{
}