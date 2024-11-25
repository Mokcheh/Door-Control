#pragma once
#include <cstdint>

class HC_SR04{
public:
    HC_SR04(const uint8_t echo, const uint8_t trig);
    uint32_t measureDistanceInCm();
private:
    void sendPulse();
    const uint8_t ECHO, TRIG;
};