#pragma once
#include <Arduino.h>

#define datapin 5

long currentMillis = 0;
long previousMillis = 0;
int interval = 1000;
float calibrationFactor = 4.5;
volatile byte pulseCount;
byte pulse1Sec = 0;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

struct myflow
{
    myflow() {}

    void IRAM_ATTR pulseCounter()
    {
        pulseCount++;
    }

    float readflow()
    {
        currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            pulse1Sec = pulseCount;
            pulseCount = 0;
            flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
            previousMillis = millis();
            flowMilliLitres = (flowRate / 60) * 1000;
            totalMilliLitres += flowMilliLitres;
        }
    return flowMilliLitres;
    }

    int totalflow(){
        currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            pulse1Sec = pulseCount;
            pulseCount = 0;
            flowRate = ((1000.0 / (millis() - previousMillis)) * pulse1Sec) / calibrationFactor;
            previousMillis = millis();
            flowMilliLitres = (flowRate / 60) * 1000;
            totalMilliLitres += flowMilliLitres;
        }
        return totalMilliLitres;
    }
};