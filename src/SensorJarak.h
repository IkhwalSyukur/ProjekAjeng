#pragma once

#include <Arduino.h>

#define trigPin1 33
#define echoPin1 25
#define trigPin2 12
#define echoPin2 13
#define trigPin3 27
#define echoPin3 26

long duration, distance;

struct jarak
{
    jarak() {}

    void begin()
    {
        pinMode(trigPin1, OUTPUT);
        pinMode(echoPin1, INPUT);
        pinMode(trigPin2, OUTPUT);
        pinMode(echoPin2, INPUT);
        pinMode(trigPin3, OUTPUT);
        pinMode(echoPin3, INPUT);
    }

    int ReadSensor(int trigpin,int echopin)
    {
        digitalWrite(trigpin, LOW);
        delayMicroseconds(10);
        digitalWrite(trigpin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigpin, LOW);
        duration = pulseIn(echopin, HIGH);
        return distance = (duration / 2) / 29.1;
    }
};
