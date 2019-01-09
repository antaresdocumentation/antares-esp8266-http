#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";
String deviceName = "your-device-name";

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

 
