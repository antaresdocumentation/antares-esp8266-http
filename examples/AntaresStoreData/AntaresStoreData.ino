#include "AntaresESPHTTP.h"

#define ACCESSKEY "b4e89ce2436b9d90:202c7b14b849c084"
#define WIFISSID "LAB IOT 2"
#define PASSWORD "labiot2018"

String projectName = "weather-station";
String deviceName = "station1";

Antares antares(ACCESSKEY);

/*
  This code will deploy data to your Antares project device with the following structure:
  {
    "Temperature": "random-value",
    "Humidity": "random-value"
  }
  For more information visit https://antares.id/id/docs.html
*/
void setup() {
  Serial.begin(115200);
  antares.begin();
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  int temp = random(25,30) ;
  int hum = random(75,90);
  antares.push("Temperature", temp);
  antares.push("Humidity", hum);
  antares.store(projectName, deviceName);
  delay(10000);
}

 
