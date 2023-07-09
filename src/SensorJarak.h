#pragma once

#include <Arduino.h>

#define trigPin1 2
#define echoPin1 4
#define trigPin2 21
#define echoPin2 22
#define trigPin3 5
#define echoPin3 18

long duration, distance, Sensor1, Sensor2, Sensor3;

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

    int ReadSensor1()
    {
        digitalWrite(trigPin1, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPin1, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin1, LOW);
        duration = pulseIn(echoPin1, HIGH);
        return distance = (duration / 2) / 29.1;
    }

    int ReadSensor2()
    {
        digitalWrite(trigPin2, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPin2, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin2, LOW);
        duration = pulseIn(echoPin2, HIGH);
        return distance = (duration / 2) / 29.1;
    }

    int ReadSensor3()
    {
        digitalWrite(trigPin3, LOW);
        delayMicroseconds(10);
        digitalWrite(trigPin3, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin3, LOW);
        duration = pulseIn(echoPin2, HIGH);
        return distance = (duration / 2) / 29.1;
    }
};
