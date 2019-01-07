#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";
String deviceName = "your-device-name";

Antares antares(ACCESSKEY);

/*
  This code will fetch the latest data from your antares project device.
  Your Antares project device must have a structure like this:
  {
    "Temperature": "some-value",
    "Humidity": "some-value"
  }
  For more information visit https://antares.id/id/docs.html
*/


void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  JsonObject& dataJson = antares.retrieveLatestData(projectName, deviceName);
  String temp = dataJson["Temperature"];
  String hum = dataJson["Humidity"];
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(", Humidity: ");
  Serial.println(hum);
  delay(10000);
}

 
