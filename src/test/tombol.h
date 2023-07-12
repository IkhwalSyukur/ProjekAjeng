#pragma once
#include <Arduino.h>

//Tombol Aktif LOW
//Switch 2 dan 3 Aktif LOW
//Switch 1 Aktif high

#define tombol1 35
#define tombol2 34
#define tombol3 39
#define switch1 23
#define switch2 14
#define switch3 32

void setup()
{
    Serial.begin(115200);
    pinMode(tombol1, INPUT);
    pinMode(tombol2, INPUT);
    pinMode(tombol3, INPUT);
    pinMode(switch1, INPUT_PULLUP);
    pinMode(switch2, INPUT_PULLUP);
    pinMode(switch3, INPUT_PULLUP);
}

void loop (){
    int data1 = digitalRead(tombol1);
    int data2 = digitalRead(tombol2);
    int data3 = digitalRead(tombol3);
    int limit1 = digitalRead(switch1);
    int limit2 = digitalRead(switch2);
    int limit3 = digitalRead(switch3);
    // Serial.print("tombol 1 = ");
    // Serial.println(data1);
    // Serial.print("tombol 2 = ");
    // Serial.println(data2);
    // Serial.print("tombol 3 = ");
    // Serial.println(data3);
    Serial.print("limit1 = ");
    Serial.println(limit1);
    Serial.print("limit2 = ");
    Serial.println(limit2);
    Serial.print("limit3 = ");
    Serial.println(limit3);
    delay(100);
}