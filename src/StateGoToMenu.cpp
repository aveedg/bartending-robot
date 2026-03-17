#include "StateGoToMenu.h"
#include "Context.h"
#include "StateReadMenu.h"
#include "Robot.h"

void StateGoToMenu::enter()
{
    flag = 0;
    ctx_->robot_->resetDistance();
    Serial.println("State: GOTOMENU");
    ctx_->robot_->indicatorLED(0x07);

    ctx_->robot_->writeMotors(-150, -150);
}
void StateGoToMenu::update()
{
    switch (flag)
    {
    case 0:
        // back up from button
        if (ctx_->robot_->getDistance() > distance) // change distance to be teeny tiny
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(0, 150); // turn right
            flag++;
        }
        break;

    case 1:
        // turn to right
        if (ctx_->robot_->getAngle() > angle) // schwervy turn?
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(150, 150);
            flag++;
        }
        break;

    case 2:
        // go to menu
        if (ctx_->robot_->getDistance() > distance1)
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(150, 0); // turn left
            flag++;
        }
        break;

    case 3:
        // turn towards menu
        if (ctx_->robot_->getAngle() > angle)
        {
            ctx_->robot_->resetDistance();
            ctx_->robot_->writeMotors(150, 150);
            flag++;
        }
        break;

    case 4:
        // go up to menu
        if (ctx_->robot_->getDistance() > distance)
            ctx_->transitionTo(new StateReadMenu);
        break;
    }
}
void StateGoToMenu::exit()
{
}