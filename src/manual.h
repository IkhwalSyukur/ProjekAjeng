#pragma once
#include <Arduino.h>

#define tombol1 35
#define tombol2 34
#define tombol3 39

struct tombol {
    tombol () {}

    void begin(){
        pinMode(tombol1,INPUT);
        pinMode(tombol2,INPUT);
        pinMode(tombol3,INPUT);
    }

    int readtombol(int tombol){
        return digitalRead(tombol);
    }
};