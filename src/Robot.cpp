#include "Robot.h"
#include "Context.h"
#include <Arduino.h>
#include <QTRSensors.h>
#include "Adafruit_TCS34725.h"
#include <Wire.h>

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
    Serial.begin(9600);
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
    pinMode(INDICATOR_LED_7, OUTPUT);
    pinMode(INDICATOR_LED_8, OUTPUT);

    pinMode(CLOCK_IN, INPUT_PULLUP);

    attachInterrupt(0, isr0_wrapper, RISING);
    attachInterrupt(5, isr1_wrapper, RISING);
    qtr.setTypeRC();
    qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3, A4, A5, A6, A7}, 8);
}

void Robot::calibrate()
{
    for (int i = 22; i < 30; i++)
    {
        digitalWrite(i, HIGH);
    }

    for (uint8_t i = 0; i < 250; i++)
    {
        qtr.calibrate();
        delay(5);
    }

    for (int i = 22; i < 30; i++)
    {
        digitalWrite(i, LOW);
    }
}

void Robot::lineFollow()
{

    if (millis() - prev_millis > time_var)
    {
        qtr.readCalibrated(sensors);

        int16_t position = qtr.readLineBlack(sensors);

        prev_error = error;
        error = (position - 3500);
        int_err = int_err + error;
        der_err = (error - prev_error);

        int16_t P = Kp * error;
        int16_t I = Ki * int_err;
        int16_t D = (Kd * der_err) / time_var;

        int16_t control = P + I + D; // want ~200 at max error

        int leftMotorSpeed = base - control;
        int rightMotorSpeed = base + control;

        Serial.print(error);
        Serial.print(", ");
        Serial.print(P);
        Serial.print(", ");
        Serial.println(D);

        // Serial.print("Left:");
        // Serial.println(leftMotorSpeed);
        // Serial.print("Right:");
        // Serial.println(rightMotorSpeed);

        writeMotors(leftMotorSpeed, rightMotorSpeed);
    }

    if (sensors[0] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_1, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_1, HIGH);
    }

    if (sensors[1] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_2, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_2, HIGH);
    }

    if (sensors[2] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_3, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_3, HIGH);
    }
    if (sensors[3] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_4, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_4, HIGH);
    }
    if (sensors[4] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_5, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_5, HIGH);
    }
    if (sensors[5] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_6, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_6, HIGH);
    }
    if (sensors[6] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_7, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_7, HIGH);
    }
    if (sensors[7] > 750)
    {
        digitalWrite(LINE_FOLLOW_LED_8, LOW);
    }
    else
    {
        digitalWrite(LINE_FOLLOW_LED_8, HIGH);
    }
}

void Robot::writeMotors(int leftMotorSpeed, int rightMotorSpeed)
{
    leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
    rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);

    if (leftMotorSpeed < 0)
    {
        digitalWrite(11, LOW);
        digitalWrite(12, HIGH);
    }
    else if (leftMotorSpeed > 0)
    {
        digitalWrite(11, HIGH);
        digitalWrite(12, LOW);
    }
    if (rightMotorSpeed < 0)
    {
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
    }
    else if (rightMotorSpeed > 0)
    {
        digitalWrite(9, HIGH);
        digitalWrite(10, LOW);
    }

    Serial.print("right: ");
    Serial.println(rightMotorSpeed);
    Serial.print("left: ");
    Serial.println(leftMotorSpeed);

    analogWrite(13, abs(leftMotorSpeed));
    analogWrite(8, abs(rightMotorSpeed));
}

bool Robot::lineLost()
{
    qtr.readCalibrated(sensors);

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
    if (digitalRead(CLOCK_IN) == LOW)
    {
        return true;
    }
    return false;
}

int Robot::readColor()
{
    long r_reading, g_reading, b_reading;

    const float targetR[] = {1100, 300, 1700, 500}; // yellow, blue, red, green
    const float targetG[] = {900, 1200, 230, 1400};
    const float targetB[] = {400, 2800, 280, 600};

    Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);

    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);
    // colorTemp = tcs.calculateColorTemperature(r, g, b);
    colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);

    int closestColor = 0;
    float minDistance = 999999;

    for (int j = 0; j < 4; j++)
    {                                                                                                    // go through each color
        float distance = sqrt(pow(r - targetR[j], 2) + pow(g - targetG[j], 2) + pow(b - targetB[j], 2)); // distance formula
        if (distance < minDistance)
        {                           // if it beats our previous minimum distance
            minDistance = distance; // update recordholder distance
            closestColor = j;       // update recordholder color
        }
    }

    return closestColor;
}

void Robot::indicatorLED(uint8_t parameter)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(INDICATOR_LED_1 + i, (parameter >> i) & 1);
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

    float angle_deg = ((r_dist - l_dist) / 160) * 180.0 / PI; // dist between wheels in mm

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
    countl = 0;
    interrupts();
}

bool Robot::checkFull()
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
    tone(7, freq, tonelength);
}

bool Robot::senseLineLeft()
{
    uint16_t sensors[8];
    qtr.readCalibrated(sensors);

    if (sensors[0] > 750 && sensors[1] > 750 && sensors[2] > 750)
    {
        return true;
    }

    return false;
}

bool Robot::senseLineRight()
{
    uint16_t sensors[8];
    qtr.readCalibrated(sensors);

    if (sensors[5] > 750 && sensors[6] > 750 && sensors[7] > 750)
    {
        return true;
    }

    return false;
}

bool Robot::beerFull()
{
    int beer = analogRead(BEER_LEVEL);
    if (beer > 230) // remeasure!!
    {
        return true;
    }
    else
        return false;
}

void Robot::initLineFollow()
{
    int16_t position = qtr.readLineBlack(sensors);
    error = (position - 3500);
    der_err = 0;
    prev_error = error;
    int_err = 0;
}
void Robot::tapDown()
{
}

void Robot::tapUp()
{
}