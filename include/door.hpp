#pragma once
#include "ultrasonic_sensor.hpp"
#include "motor.hpp"
#include <cstdint> 

class Door{
public:
    Door(L298N& motor, HC_SR04& ultrasonic, uint16_t travel);
    void operate();
    void calibrate();
private:
    L298N& motorDriver;
    HC_SR04& ultrasonic;
    uint16_t travelDistance;
    void slideUp();
    void slideDown(uint16_t slideTime = 4100);
    void stop();
};