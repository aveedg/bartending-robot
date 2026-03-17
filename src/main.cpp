#include <Arduino.h>
#include "Context.h"
#include "StateInit.h"
#include "Robot.h"

Context *ctx;
Robot *robot;

void setup()
{
  robot = new Robot();
  robot->begin();

  ctx = new Context(new StateInit, robot);
}

void loop()
{
  ctx->update();
  // robot->lineFollow();
}
