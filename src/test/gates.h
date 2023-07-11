#pragma once
#include <Arduino.h>

#define motor1open 19
#define motor1close 18
#define motor2open 16
#define motor2close 17
#define motor3open 22
#define motor3close 21
#define switch1 23
#define switch2 32
#define switch3 14

void setup()
{
    Serial.begin(115200);
    pinMode(motor1open, OUTPUT);
    pinMode(motor1close, OUTPUT);
    pinMode(motor2open, OUTPUT);
    pinMode(motor2close, OUTPUT);
    pinMode(motor3open, OUTPUT);
    pinMode(motor3close, OUTPUT);
    pinMode(switch1, INPUT);
    pinMode(switch2, INPUT);
    pinMode(switch3, INPUT);
}

void loop()
{
    digitalWrite(motor1open, HIGH);
    digitalWrite(motor1close, LOW);
    delay(500);
    digitalWrite(motor1open,LOW);
    digitalWrite(motor1close,HIGH);
    if (digitalRead(switch1)==1){
        digitalWrite(motor1open,LOW);
        digitalWrite(motor1close,LOW);
    }
    Serial.print("kondisi switch = ");
    Serial.println(digitalRead(switch1));
}