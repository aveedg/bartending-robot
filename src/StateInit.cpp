#include "StateInit.h"
#include "Context.h"
#include "StateMaze.h"
#include "Robot.h"
#include <QTRSensors.h>
#include <Arduino.h>

QTRSensors qtr;

void StateInit::enter()
{
    ctx_->robot_->calibrate();
    ctx_->transitionTo(new StateMaze);
}
void StateInit::update()
{
}
void StateInit::exit()
{
}