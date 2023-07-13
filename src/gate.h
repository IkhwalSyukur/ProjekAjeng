#pragma once
#include <Arduino.h>

#define motor1open 19
#define motor1close 18
#define motor2open 16
#define motor2close 17
#define motor3open 22
#define motor3close 21
#define limit1 23

struct gates
{
    gates() {}

    void begin()
    {
        pinMode(motor1open, OUTPUT);
        pinMode(motor1close, OUTPUT);
        pinMode(motor2open, OUTPUT);
        pinMode(motor2close, OUTPUT);
        pinMode(motor3open, OUTPUT);
        pinMode(motor3close, OUTPUT);
        pinMode(limit1, INPUT_PULLUP);
    }

    void gateopenfull(int open, int close)
    {
        digitalWrite(open, HIGH);
        digitalWrite(close, LOW);
        vTaskDelay(3200);
        digitalWrite(open, LOW);
        digitalWrite(close, LOW);
        vTaskDelay(10);
    }

    void gateopenhalf(int open, int close)
    {
        digitalWrite(open, HIGH);
        digitalWrite(close, LOW);
        vTaskDelay(1600);
        digitalWrite(open, LOW);
        digitalWrite(close, LOW);
        vTaskDelay(10);
    }

    void gateclosefull(int open, int close, int limit)
    {
        digitalWrite(open, LOW);
        digitalWrite(close, HIGH);
        vTaskDelay(3200);
        digitalWrite(open, LOW);
        digitalWrite(close, LOW);
        vTaskDelay(10);
        // while (digitalRead(limit) == 0)
        // {
        //     digitalWrite(open,LOW);
        //     digitalWrite(close,LOW);
        // }
    }

    void gateclosehalf(int open, int close)
    {
        digitalWrite(open, LOW);
        digitalWrite(close, HIGH);
        vTaskDelay(1600);
        digitalWrite(open, LOW);
        digitalWrite(close, LOW);
        vTaskDelay(10);
    }
};