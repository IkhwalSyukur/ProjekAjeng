#pragma once
#include <Arduino.h>

#define trigPin1 2
#define echoPin1 4
#define trigPin2 21
#define echoPin2 22
#define trigPin3 5
#define echoPin3 18

long duration, distance1, distance2, distance3;

void setup()
{
    Serial.begin(115200);
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
    pinMode(trigPin3, OUTPUT);
    pinMode(echoPin3, INPUT);
}

void loop()
{
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    duration = pulseIn(echoPin1, HIGH);
    distance1 = (duration / 2) / 29.1;

    digitalWrite(trigPin2, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    duration = pulseIn(echoPin2, HIGH);
    distance2 = (duration / 2) / 29.1;

    digitalWrite(trigPin3, LOW);
    delayMicroseconds(10);
    digitalWrite(trigPin3, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin3, LOW);
    duration = pulseIn(echoPin3, HIGH);
    distance3 = (duration / 2) / 29.1;

    Serial.print("Jarak 1 = ");
    Serial.println(distance1);
    Serial.print("Jarak 2 = ");
    Serial.println(distance2);
    Serial.print("Jarak 3 = ");
    Serial.println(distance3);

    delay(500);

}