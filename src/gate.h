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

    void gate1open (){
        digitalWrite(motor1open,HIGH);
        digitalWrite(motor1close,LOW);
    }

    void gate1close (){
        digitalWrite(motor1open,LOW);
        digitalWrite(motor1close,HIGH);
    }

    void gate1stop (){
        digitalWrite(motor1open,LOW);
        digitalWrite(motor1close,LOW);
    }

    void gate2open (){
        digitalWrite(motor2open,HIGH);
        digitalWrite(motor2close,LOW);
    }

    void gate2close (){
        digitalWrite(motor2open,LOW);
        digitalWrite(motor2close,HIGH);
    }

    void gate2stop (){
        digitalWrite(motor2open,LOW);
        digitalWrite(motor2close,LOW);
    }

    void gate3open (){
        digitalWrite(motor3open,HIGH);
        digitalWrite(motor3close,LOW);
    }

    void gate3close (){
        digitalWrite(motor3open,LOW);
        digitalWrite(motor3close,HIGH);
    }

    void gate3stop (){
        digitalWrite(motor3open,LOW);
        digitalWrite(motor3close,LOW);
    }

    void stop (){
        digitalWrite(motor1open,LOW);
        digitalWrite(motor1close,LOW);
        digitalWrite(motor2open,LOW);
        digitalWrite(motor2close,LOW);
        digitalWrite(motor3open,LOW);
        digitalWrite(motor3close,LOW);
    }
};