#pragma once
#include <Arduino.h>


#define switch1 23
#define switch2 32
#define switch3 14

struct  mylimit {
    mylimit () {}

    void begin (){
        pinMode(switch1,INPUT);
        pinMode(switch2,INPUT);
        pinMode(switch3,INPUT);
    }

    int readlimit1 (){
        return digitalRead(switch1);
    }

    int readlimit2 (){
        return digitalRead(switch2);
    }

    int readlimit3 (){
        return digitalRead(switch3);
    }
};