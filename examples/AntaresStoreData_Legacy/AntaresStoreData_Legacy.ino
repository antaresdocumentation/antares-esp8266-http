/*
  ============================= WARNING ================================
  This example is not recommended as it uses port 8080 (non-secure HTTP)
  for connecting to Antares.
  ============================= WARNING ================================
  This code deploys data to your Antares project device with the following structure:
  {
    "Temperature": "random-value",
    "Humidity": "random-value"
  }
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-device-name"

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  /* Use wifiConnectionNonSecure instead if you don't want to use HTTPS
   * and avoid SNTP matching */
  //antares.wifiConnectionNonSecure(WIFISSID,PASSWORD);
}

void loop() {
  int sizeData = 2;
  String dataName[sizeData],dataValue[sizeData];
  dataName[0] = "Temperature";
  dataName[1] = "Humidity";

  dataValue[0] = (String)random(50,100);
  dataValue[1] = (String)random(50,100);
  Serial.println(antares.storeData(projectName, deviceName, dataName, dataValue, sizeData));
  delay(10000);
}
