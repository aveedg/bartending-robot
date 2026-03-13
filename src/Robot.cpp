#include "Robot.h"
#include "Context.h"
#include <Arduino.h>
#include <QTRSensors.h>

QTRSensors qtr;
volatile long countr = 0;
volatile long countl = 0;

extern Robot *robot;

void isr0_wrapper()
{
    robot->isr0();
}

void isr1_wrapper()
{
    robot->isr1();
}

void Robot::begin()
{
    pinMode(LINE_FOLLOW_LED_1, OUTPUT);
    pinMode(LINE_FOLLOW_LED_2, OUTPUT);
    pinMode(LINE_FOLLOW_LED_3, OUTPUT);
    pinMode(LINE_FOLLOW_LED_4, OUTPUT);
    pinMode(LINE_FOLLOW_LED_5, OUTPUT);
    pinMode(LINE_FOLLOW_LED_6, OUTPUT);
    pinMode(LINE_FOLLOW_LED_7, OUTPUT);
    pinMode(LINE_FOLLOW_LED_8, OUTPUT);

    pinMode(LINE_SENSOR_1, INPUT);
    pinMode(LINE_SENSOR_2, INPUT);
    pinMode(LINE_SENSOR_3, INPUT);
    pinMode(LINE_SENSOR_4, INPUT);
    pinMode(LINE_SENSOR_5, INPUT);
    pinMode(LINE_SENSOR_6, INPUT);
    pinMode(LINE_SENSOR_7, INPUT);
    pinMode(LINE_SENSOR_8, INPUT);

    // Debug LED pins

    pinMode(LEFT_A, INPUT);
    pinMode(LEFT_B, INPUT);
    pinMode(EN_A, OUTPUT);
    pinMode(IN_3, OUTPUT);
    pinMode(IN_4, OUTPUT);

    pinMode(RIGHT_A, INPUT);
    pinMode(RIGHT_B, INPUT);
    pinMode(EN_B, OUTPUT);
    pinMode(IN_1, OUTPUT);
    pinMode(IN_2, OUTPUT);

    pinMode(RED, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(GREEN, OUTPUT);

    pinMode(INDICATOR_LED_1, OUTPUT);
    pinMode(INDICATOR_LED_2, OUTPUT);
    pinMode(INDICATOR_LED_3, OUTPUT);
    pinMode(INDICATOR_LED_4, OUTPUT);
    pinMode(INDICATOR_LED_5, OUTPUT);
    pinMode(INDICATOR_LED_6, OUTPUT);
    pinMode(INDICATOR_LED_1, OUTPUT);
    pinMode(INDICATOR_LED_7, OUTPUT);
    pinMode(INDICATOR_LED_8, OUTPUT);

    attachInterrupt(0, isr0_wrapper, RISING);
    attachInterrupt(5, isr1_wrapper, RISING);
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, 8);
}

void Robot::calibrate()
{
    for (int i = 46; i < 54; i++)
    {
        digitalWrite(i, HIGH);
    }

    for (uint8_t i = 0; i < 250; i++)
    {
        qtr.calibrate();
        delay(20);
    }

    for (int i = 46; i < 54; i++)
    {
        digitalWrite(i, LOW);
    }
}

void Robot::lineFollow()
{
    uint16_t sensors[8];
    int16_t error = 0;
    int16_t prev_error = 0;
    int16_t int_err = 0;
    int16_t der_err = 0;
    float Kp = 0.04;
    float Ki = 0;
    float Kd = 0.01;
    int16_t prev_D = 0;
    unsigned long prev_millis = 0;
    int flag = 0;
    int base = 120;

    qtr.readCalibrated(sensors);

    int16_t position = qtr.readLineBlack(sensors);

    prev_error = error;
    error = (position - 3500);
    int_err = int_err + error;
    der_err = (error - prev_error);

    int16_t P = Kp * error;
    int16_t I = Ki * int_err;
    int16_t D = (Kd * der_err * 0.2) + (0.8 * prev_D);
    prev_D = D;

    int16_t control = P + I + D; // want ~200 at max error

    int leftMotorSpeed = base + control;
    int rightMotorSpeed = base - control;

    writeMotors(rightMotorSpeed, leftMotorSpeed);
}

void Robot::writeMotors(int rightMotorSpeed, int leftMotorSpeed)
{
    leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);

    if (leftMotorSpeed < 0)
    {
        digitalWrite(IN_3, LOW);
        digitalWrite(IN_4, HIGH);
    }
    else if (leftMotorSpeed > 0)
    {
        digitalWrite(IN_3, HIGH);
        digitalWrite(IN_4, LOW);
    }
    if (rightMotorSpeed < 0)
    {
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
    }
    else if (leftMotorSpeed > 0)
    {
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
    }

    analogWrite(13, abs(leftMotorSpeed));
    analogWrite(8, abs(rightMotorSpeed));
}

bool Robot::lineLost()
{
    uint16_t sensors[8];
    for (int i = 0; i < 8; i++)
    {
        if (sensors[i] > 750)
        {
            return false;
        }
    }
    return true;
}

bool Robot::clockIn()
{
    if (digitalRead(CLOCK_IN) == HIGH)
    {
        return true;
    }
    return false;
}

void Robot::moveArm()
{
}

int Robot::readColor()
{
    long r_reading, g_reading, b_reading;

    const float targetR[] = {
        290.00,
        115.08,
        106.22,
    }; // fill // Black Red Blue Green White
    const float targetG[] = {
        720.00,
        785.00,
        855.89,
    }; // fill
    const float targetB[] = {
        175.00,
        235.00,
        156.12,
    }; // fill
    const char *colorNames[] = {"Red", "Blue", "Green", "Yellow"};
    r_reading = g_reading = b_reading = 0;

    digitalWrite(RED, HIGH);
    delayMicroseconds(350);
    for (int i = 0; i < 4; i++)
    {
        r_reading += analogRead(PHOTOIN);
    }
    digitalWrite(RED, LOW);
    delay(1);

    digitalWrite(BLUE, HIGH);
    delayMicroseconds(360);
    for (int i = 0; i < 4; i++)
    {
        b_reading += analogRead(PHOTOIN);
    }
    digitalWrite(BLUE, LOW);
    delay(1);

    digitalWrite(GREEN, HIGH);
    delayMicroseconds(275);
    for (int i = 0; i < 4; i++)
    {
        g_reading += analogRead(PHOTOIN);
    }
    digitalWrite(GREEN, LOW);

    float r = r_reading;
    float g = g_reading;
    float b = b_reading;

    int closestColor = 0;
    float minDistance = 999999;

    for (int j = 0; j < 5; j++)
    {                                                                                                    // go through each color
        float distance = sqrt(pow(r - targetR[j], 2) + pow(g - targetG[j], 2) + pow(b - targetB[j], 2)); // distance formula
        if (distance < minDistance)
        {                           // if it beats our previous minimum distance
            minDistance = distance; // update recordholder distance
            closestColor = j;       // update recordholder color
        }
    }

    return closestColor;

    delay(200);
}

void Robot::indicatorLED(uint8_t indicator)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(46 + i, (indicator >> i) & 1);
    }
}

void Robot::isr0()
{
    int RB_Value = digitalRead(3);
    if (RB_Value == HIGH)
    {
        countr++;
    }
    if (RB_Value == LOW)
    {
        countr--;
    }
}

void Robot::isr1()
{
    int LB_Value = digitalRead(19);
    if (LB_Value == HIGH)
    {
        countl++;
    }
    if (LB_Value == LOW)
    {
        countl--;
    }
}

void Robot::pivotRight()
{
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);

    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);

    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);

    digitalWrite(13, HIGH);
    digitalWrite(8, HIGH);
}

void Robot::pivotLeft()
{
    digitalWrite(13, LOW);
    digitalWrite(8, LOW);

    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);

    digitalWrite(11, LOW);
    digitalWrite(12, HIGH);

    digitalWrite(13, HIGH);
    digitalWrite(8, HIGH);
}

float Robot::getAngle()
{
    long r_counts;
    long l_counts;

    noInterrupts();
    r_counts = countr;
    l_counts = countl;
    interrupts();

    float r_dist = (r_counts / 966.0) * 188.49;
    float l_dist = (l_counts / 966.0) * 188.49;

    float angle_deg = ((r_dist - l_dist) / 150) * 180.0 / PI; // dist between wheels in mm

    return angle_deg;
}

float Robot::getDistance()
{
    long counts;

    noInterrupts();
    counts = countr;
    interrupts();

    float distance = (counts / 966.0) * 188.49;

    return distance;
}

void Robot::resetDistance()
{
    noInterrupts();
    countr = 0;
    interrupts();
}

void Robot::backwardLineFollow()
{
}

int Robot::checkFull()
{
}

void Robot::playSong()
{
    int pauseBetweenNotes = 0;
    int thisNote;

    int melody[] = {
        NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4,
        NOTE_B4, NOTE_B4, NOTE_B4,
        NOTE_A4, NOTE_A4, NOTE_A4,
        NOTE_B4, NOTE_D5, NOTE_D5,

        NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4,
        NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
        NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4,
        NOTE_G4,

        NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4,
        NOTE_B4, NOTE_B4, NOTE_B4,
        NOTE_A4, NOTE_A4, NOTE_A4,
        NOTE_B4, NOTE_D5, NOTE_D5,

        NOTE_B4, NOTE_A4, NOTE_G4, NOTE_A4,
        NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
        NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4,
        NOTE_G4, NOTE_D5};

    // note durations: 4 = quarter note, 8 = eighth note, etc.:
    int noteDurations[] = {
        4, 4, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 4, 4, 4, 4, 4, 4, 2, 4, 4, 2, 4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 3, 4};

    for (thisNote = 0; thisNote < 52; thisNote++)
    {
        // e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        long noteDuration = (1000 / noteDurations[thisNote]);
        mytone(melody[thisNote], noteDuration);

        pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
    }
    thisNote = 0;
}

void Robot::mytone(int freq, long tonelength)
{
    tone(8, freq, tonelength);
}
