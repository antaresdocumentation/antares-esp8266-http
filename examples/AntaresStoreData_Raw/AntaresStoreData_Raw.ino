/*
  This code will send "Hello!" followed by an increasing integer
  every 10 seconds.
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESP8266HTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

#define projectName "your-project-name"
#define deviceName "your-device-name"

AntaresESP8266HTTP antares(ACCESSKEY);

int counter = 0;

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
  /* Use wifiConnectionNonSecure instead if you don't want to use HTTPS
   * and avoid SNTP matching */
  //antares.wifiConnectionNonSecure(WIFISSID,PASSWORD);
}

void loop() {
  String text = "Hello! ";
  text += String(counter);
  // Send the raw text into your Antares device
  antares.sendRaw(text, projectName, deviceName);
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // antares.sendRawNonSecure(text, projectName, deviceName);
  counter++;
  delay(10000);
}
