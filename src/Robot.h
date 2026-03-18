#ifndef ROBOT_H
#define ROBOT_H

#include <Arduino.h>

#define PHOTOIN A8
#define CLOCK_IN 45
#define BEER_LEVEL A15

#define LINE_SENSOR_1 A0
#define LINE_SENSOR_2 A1
#define LINE_SENSOR_3 A2
#define LINE_SENSOR_4 A3
#define LINE_SENSOR_5 A4
#define LINE_SENSOR_6 A5
#define LINE_SENSOR_7 A6
#define LINE_SENSOR_8 A7

#define DEBUG_MOTOR_LED

#define LINE_FOLLOW_LED_1 32 // 22
#define LINE_FOLLOW_LED_2 33 // 23
#define LINE_FOLLOW_LED_3 34 // 24
#define LINE_FOLLOW_LED_4 35 // 25
#define LINE_FOLLOW_LED_5 36 // 26
#define LINE_FOLLOW_LED_6 37 // 27
#define LINE_FOLLOW_LED_7 38 // 28
#define LINE_FOLLOW_LED_8 39 // 29

#define LEFT_A 2
#define LEFT_B 3
#define EN_A 13
#define IN_3 9
#define IN_4 10

#define RIGHT_A 18
#define RIGHT_B 19
#define EN_B 8
#define IN_1 11
#define IN_2 12

#define RED 44
#define BLUE 43
#define GREEN 42
#define YELLOW 41

#define INDICATOR_LED_1 29 // 39
#define INDICATOR_LED_2 28 // 38
#define INDICATOR_LED_3 27 // 37
#define INDICATOR_LED_4 26 // 36
#define INDICATOR_LED_5 25 // 35
#define INDICATOR_LED_6 24 // 34
#define INDICATOR_LED_7 23 // 33
#define INDICATOR_LED_8 22 // 32

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

class Robot
{
private:
    void mytone(int freq, long tonelength);
    uint16_t sensors[8];
    int16_t error = 0;
    int16_t der_err = 0;
    int16_t prev_error = 0;
    int16_t int_err = 0;

    float Kp = 0.08;
    float Ki = 0;
    float Kd = 3;
    int base = 150;
    int prev_millis = 0;
    int time_var = 20;

public:
    void begin();
    void lineFollow();
    bool lineLost();
    bool clockIn();
    void indicatorLED(uint8_t parameter);
    int readColor();
    float getDistance();
    void resetDistance();
    float getAngle();
    void tapDown();
    void tapUp();
    bool checkFull();
    void isr0();
    void isr1();
    void playSong();
    void calibrate();
    bool senseLineRight();
    bool senseLineLeft();
    void writeMotors(int r, int l);
    bool beerFull();
    void initLineFollow();
};

#endif