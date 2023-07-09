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

    int readtombol1(){
        return digitalRead(tombol1);
    }

    int readtombol2(){
        return digitalRead(tombol2);
    }

    int readTombol3(){
        return digitalRead(tombol3);
    }
};