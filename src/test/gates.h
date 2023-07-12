#pragma once
#include <Arduino.h>

#define motor1open 19
#define motor1close 18
#define motor2open 16
#define motor2close 17
#define motor3open 22
#define motor3close 21
#define switch1 23
#define switch2 14
#define switch3 32
#define tombol1 35
#define tombol2 34
int count = 0;
int butstat1 = 0;
int butstat2 = 0;

void setup()
{
    Serial.begin(115200);
    pinMode(motor1open, OUTPUT);
    pinMode(motor1close, OUTPUT);
    pinMode(motor2open, OUTPUT);
    pinMode(motor2close, OUTPUT);
    pinMode(motor3open, OUTPUT);
    pinMode(motor3close, OUTPUT);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(switch2, INPUT_PULLUP);
    pinMode(switch3, INPUT_PULLUP);
    pinMode(tombol1, INPUT);
    pinMode(tombol2, INPUT);
}

void loop()
{
    int limit1 = digitalRead(switch1);
    int butstat1 = digitalRead(tombol1);
    int butstat2 = digitalRead(tombol2);

    if (count == 0 && butstat1 == 0)
    {
        count = 1;
    }
    if (count == 1)
    {
        digitalWrite(motor1open, HIGH);
        digitalWrite(motor1close, LOW); // Buka
        delay(3200);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW);
        delay(10);
    }

    if (butstat2 == 0)
    {

        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, HIGH); // Tutup
    }
    if (limit1 == 0)
    {
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW); // Stop
    }

    // Serial.print("kondisi switch = ");
    // Serial.println(limit1);
    // Serial.print("count = ");
    // Serial.println(count);
    // digitalWrite(motor1open, LOW);
    // digitalWrite(motor1close, HIGH); // Tutup
    // if (limit1 == 0)
    // {
    //     digitalWrite(motor1open, LOW);
    //     digitalWrite(motor1close, LOW); // Stop
    //     count = 0;
    // }
}