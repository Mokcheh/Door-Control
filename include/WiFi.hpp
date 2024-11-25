#pragma once
#include <Arduino.h>
#include <cstdint>

namespace wifi{
    void connect(const char* ssid, const char* pswd);
    void ensureConnection(const char* ssid, const char* pswd);
};

namespace firebase{
    void login(const char* key, const char* url, const char* mail, const char* psswd);
    uint8_t getOrder();
    bool getDoorStatus();
    void clearOrder();
    void setDoorStatus(bool status);
    bool getAuto();
};
