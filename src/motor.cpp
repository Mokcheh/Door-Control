#include "motor.hpp"
#include <Arduino.h>

L298N::L298N(const uint8_t in1, const uint8_t in2):
IN1(in1), IN2(in2)
{
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
}

void L298N::spin(const direction d)
{
    uint8_t dComplement;
    if(d == 1)
        dComplement = 0;
    else
        dComplement = 1;
    digitalWrite(IN1, d);
    digitalWrite(IN2, dComplement);
}

void L298N::stop(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
}