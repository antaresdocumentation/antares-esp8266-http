#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";
String deviceName = "your-device-name";

Antares antares(ACCESSKEY);

/*
  This code will fetch the latest data from your antares project device.
  For more information visit https://antares.id/id/docs.html
*/


void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  antares.retrieveLatestData(projectName, deviceName);
  delay(10000);
}
