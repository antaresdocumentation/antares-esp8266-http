/*
  This code will fetch and print the latest data from your antares project device.
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
  String data = antares.getRaw(projectName, deviceName); // Get data
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // String data = antares.getRawNonSecure(projectName, deviceName);

  Serial.println(data); // Print data to serial monitor
  delay(10000);
}
