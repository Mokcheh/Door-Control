#include <Arduino.h>
#include "door.hpp"
#include "WiFi.hpp"

enum doorOrder: uint8_t{
    STOP, OPEN, CLOSE
};

Door::Door(L298N& motor, HC_SR04& ultrasonic, uint16_t travel)
    : motorDriver(motor), ultrasonic(ultrasonic), travelDistance(travel)
{

}

void Door::calibrate()
{
    if(ultrasonic.measureDistanceInCm() > 2)
    {
        motorDriver.spin(FORWARD);
        delay(1000);
        motorDriver.spin(REVERSE);
        while(ultrasonic.measureDistanceInCm() > 2)
        {
            delay(80);
        }
        delay(600);
        motorDriver.stop();
    }
}

void Door::operate()
{
    auto order = firebase::getOrder();
    switch(order)
    {
    case STOP:
        stop();
        break;
    case OPEN:
    {
        slideUp();
        if(!firebase::getAuto())
        {
            firebase::setDoorStatus(1);
            firebase::clearOrder();
            break;
        }
        else
        {
            delay(800);
            uint32_t highestMeasure = ultrasonic.measureDistanceInCm() + 1;
            delay(200);
            while((highestMeasure - ultrasonic.measureDistanceInCm()) <= 3)
            {
                delay(300);
            }

            while(highestMeasure > (ultrasonic.measureDistanceInCm() + 1))
            {
                delay(2000);
            }         
        }
    }
    case CLOSE:
        slideDown();
        firebase::setDoorStatus(0);
        firebase::clearOrder();
        break;
    default:
        Serial.println("Unknown order!");
        break;
    }
}

void Door::slideUp()
{
    motorDriver.spin(FORWARD);
    do{
        delay(80);
    }while(ultrasonic.measureDistanceInCm() < travelDistance);
    stop();
}

void Door::slideDown(uint16_t slideTime)
{
    motorDriver.spin(REVERSE);
    do{
        delay(200);
    }while(ultrasonic.measureDistanceInCm() > 2);

}

void Door::stop(){
    motorDriver.stop();
}