#include <Arduino.h>
#include "WiFi.hpp"
#include "ultrasonic_sensor.hpp"
#include "motor.hpp"
#include "door.hpp"
#include "credentials.hpp"


namespace external{
  static HC_SR04 ultrasonic(D1, D2);
  static L298N motorDriver(D7, D6);
  static Door door(motorDriver, ultrasonic, 13);
}




void setup() 
{
  Serial.begin(115200);
  wifi::connect(ssid, password);
  firebase::login(api_key, db_url, email, db_password);
  external::door.calibrate();
}


void loop() 
{
  wifi::ensureConnection(ssid, password);
  external::door.operate();
}
