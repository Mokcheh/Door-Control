#pragma once
#include <cstdint>

enum direction : uint8_t{
    REVERSE, FORWARD
};

class L298N{
public:
    L298N(const uint8_t in1, const uint8_t in2);
    void spin(const direction d);
    void stop();
private:
    const uint8_t IN1, IN2;
};