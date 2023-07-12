#pragma once

#define DEBUG

#include <Arduino.h>

// #define trigPin1 2
// #define echoPin1 4
// #define trigPin2 21
// #define echoPin2 22
// #define trigPin3 5
// #define echoPin3 18

#define trigPin1 33
#define echoPin1 25
#define trigPin2 12
#define echoPin2 13
#define trigPin3 27
#define echoPin3 26

typedef struct
{
    int distance[3];

    void begin();
    int readSensor(int trig, int echo);
    static void _staticTaskFunc(void *pvParam);
    void _taskFunc();
} Distance;

/* STATIC */ void Distance::_staticTaskFunc(void *pvParam)
{
    Distance *handler = reinterpret_cast<Distance *>(pvParam);
    handler->_taskFunc();
}

Distance ultrasonic;

void Distance::begin()
{
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);

    xTaskCreate(_staticTaskFunc, "Read", 1024 * 2, NULL, 10, NULL);
}

int Distance::readSensor(int trig, int echo)
{
    digitalWrite(trig, LOW);
    delayMicroseconds(10);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH);
    return (duration / 2) / 29.1;
}

void Distance::_taskFunc()
{
    Serial.println("Ultrasonic Sensor Task Started !");
    while (1)
    {
        ultrasonic.distance[0] = ultrasonic.readSensor(trigPin1, echoPin1);
        ultrasonic.distance[1] = ultrasonic.readSensor(trigPin2, echoPin2);
        ultrasonic.distance[2] = ultrasonic.readSensor(trigPin3, echoPin3);
#ifdef DEBUG
        Serial.printf("distance 1: %d\n", ultrasonic.distance[0]);
        Serial.printf("distance 2: %d\n", ultrasonic.distance[1]);
        Serial.printf("distance 3: %d\n", ultrasonic.distance[2]);
        Serial.println("==================");
#endif
        vTaskDelay(500);
    }
    vTaskDelete(NULL);
}