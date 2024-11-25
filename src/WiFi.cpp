#include "WiFi.hpp"
#include "ESP8266WiFi.h"
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include "credentials.hpp"


static FirebaseData fbdo;
static FirebaseAuth auth;
static FirebaseConfig config;



namespace wifi{
  void connect(const char* ssid, const char* pswd)
  {
    WiFi.begin(ssid, pswd);
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
      Serial.print(".");
    }
    Serial.println("Connected to WIFI");
    Serial.print("IP : ");
    Serial.println(WiFi.localIP());
  }

  void ensureConnection(const char* ssid, const char* pswd)
  {
    if(WiFi.status() != WL_CONNECTED)
    {
      connect(ssid, pswd);
      firebase::login(api_key, db_url, email, db_password);
    }
  }
};



namespace firebase{
  void login(const char* key, const char* url, const char* mail, const char* psswd)
  {
    config.api_key = key;
    config.database_url = url;
    auth.user.email = mail;
    auth.user.password = psswd;

    config.token_status_callback = tokenStatusCallback;
    config.max_token_generation_retry = 5;
    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);
    Serial.println("Getting User UID");
    while ((auth.token.uid) == "") {
      Serial.print('.');
      delay(500);
    }
    auto uid = auth.token.uid.c_str();
    Serial.print("User UID: ");
    Serial.println(uid);
  }

  uint8_t getOrder(){
    if(Firebase.RTDB.getInt(&fbdo, "/order"))
    {
      return fbdo.intData();
    }
    return 0;
  }
};


bool firebase::getDoorStatus()
{
  if(Firebase.RTDB.getBool(&fbdo, "/door"))
    return fbdo.boolData();
  return 0;
}

void firebase::clearOrder()
{
  if(Firebase.RTDB.setInt(&fbdo, "/order", 0))
  {
    Serial.println("Order cleared!");
  }else
  {
    Serial.println("Failed to clearOrder");
    Serial.print("Error code : ");
    Serial.println(fbdo.errorReason());
  }
}

void firebase::setDoorStatus(bool status)
{
  if (Firebase.RTDB.setBool(&fbdo, "/door", status))
    Serial.println("Door status updated to true!");
  else 
  {
    Serial.println("Failed to update door status");
    Serial.print("Error code : ");
    Serial.println(fbdo.errorReason());
  }
}


bool firebase::getAuto()
{
    if(Firebase.RTDB.getBool(&fbdo, "/auto"))
    return fbdo.boolData();
  return 0;
}