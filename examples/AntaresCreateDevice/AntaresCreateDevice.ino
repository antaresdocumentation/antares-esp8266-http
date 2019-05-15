/*
  This code creates a new device to your Antares project.
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"

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
  Serial.println(antares.createDevice(projectName,"test3"));
  //Serial.println(retrieveAllDevice(projectName));
  //Serial.println(antares.storeData(projectName, "test1", (String)random(50,100), "Celcius"));
  //Serial.println(antares.retrieveAllData(projectName, deviceName));
  //Serial.println(antares.retrieveLatestData(projectName, deviceName));
  delay(10000);
}
