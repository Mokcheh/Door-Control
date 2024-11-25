#include <Arduino.h>
#include "ultrasonic_sensor.hpp"


HC_SR04::HC_SR04(const uint8_t echo, const uint8_t trig):
    ECHO(echo), TRIG(trig)
{
    pinMode(ECHO, INPUT);
    pinMode(TRIG, OUTPUT);
}

void HC_SR04::sendPulse()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
}

uint32_t HC_SR04::measureDistanceInCm()
{
    sendPulse();
    const uint32_t TRAVEL_TIME = pulseIn(ECHO, HIGH) / 2;
    const uint32_t SPEED_OF_SOUND = 29;
    const uint32_t DISTANCE = TRAVEL_TIME / SPEED_OF_SOUND;
    return DISTANCE;
}