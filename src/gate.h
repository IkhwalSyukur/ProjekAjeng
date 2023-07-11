#pragma once
#include <Arduino.h>

#define motor1open 19
#define motor1close 18
#define motor2open 16
#define motor2close 17
#define motor3open 22
#define motor3close 21

struct gates{
    gates () {}

    void begin (){
        pinMode(motor1open,OUTPUT);
        pinMode(motor1close,OUTPUT);
        pinMode(motor2open,OUTPUT);
        pinMode(motor2close,OUTPUT);
        pinMode(motor3open,OUTPUT);
        pinMode(motor3close,OUTPUT);
    }

    void gateopen (int open,int close){
        digitalWrite(open,HIGH);
        digitalWrite(close,LOW);
    }

    void gateclose (int open,int close){
        digitalWrite(open,LOW);
        digitalWrite(close,HIGH);
    }

    void gatestop (int open,int close){
        digitalWrite(open,LOW);
        digitalWrite(close,LOW);
    }
};