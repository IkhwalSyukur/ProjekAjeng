#pragma once
#include <Arduino.h>

#define motor1open 19
#define motor1close 18
#define limit1 23
#define tombolbuka 15
#define tombolsetengah 2
#define tomboltutup 4

int kondisi;
int limstat;
int butstat;

void setup()
{
    Serial.begin(115200);
    pinMode(motor1open, OUTPUT);
    pinMode(motor1close, OUTPUT);
    pinMode(limit1, INPUT_PULLUP);
    pinMode(tombolbuka, INPUT_PULLUP);
    pinMode(tombolsetengah,INPUT_PULLUP);
    pinMode(tomboltutup,INPUT_PULLUP);
}

void loop()
{
    Serial.print("Kondisi = ");
    Serial.println(kondisi);
    Serial.print("tombol = ");
    Serial.print(digitalRead(tombolbuka));
    Serial.print(digitalRead(tombolsetengah));
    Serial.print(digitalRead(tomboltutup));
    Serial.println(digitalRead(limit1));

    while (kondisi == 0 && digitalRead(tombolbuka) == 0)
    {
        digitalWrite(motor1open, HIGH);
        digitalWrite(motor1close, LOW); // Buka
        delay(3200);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW);
        delay(100);
        kondisi=2;
    }

    while (kondisi == 0 && digitalRead(tombolsetengah) == 0)
    {
        digitalWrite(motor1open, HIGH);
        digitalWrite(motor1close, LOW); // Buka
        delay(1600);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW);
        delay(100);
        kondisi=1;
    }

    while (kondisi == 2 && digitalRead(tomboltutup) == 0)
    {
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, HIGH); // Tutup
        while (digitalRead(limit1) == 0)
        {
            digitalWrite(motor1open, LOW);
            digitalWrite(motor1close, LOW); // Stop
            kondisi = 0;
        }
    }

    while (kondisi == 2 && digitalRead(tombolsetengah) == 0)
    {
        
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, HIGH); // Tutup
        delay(1600);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW);
        delay(100);
        kondisi=1;
    }

    while (kondisi == 1 && digitalRead(tombolbuka) == 0)
    {
        digitalWrite(motor1open, HIGH);
        digitalWrite(motor1close, LOW); // Buka
        delay(1600);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW); 
        delay(100);
        kondisi=2;
    }

    while (kondisi == 1 && digitalRead(tomboltutup) == 0)
    {
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, HIGH); // Tutup
        delay(1600);
        digitalWrite(motor1open, LOW);
        digitalWrite(motor1close, LOW);
        delay(100);
        kondisi=0;
    }
    
    delay(500);
}