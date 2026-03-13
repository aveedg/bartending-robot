#include "StateSong.h"
#include "Context.h"
#include "StateMaze.h"
#include "Robot.h"
#include <Arduino.h>

#include <SPI.h>

#define COPI 51
#define SCK 52
#define CS 24

void StateSong::enter()
{
    ctx_->robot_->pivotLeft();
}
void StateSong::update()
{
    ctx_->robot_->playSong();
}

void StateSong::exit()
{
}
