#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";

Antares antares(ACCESSKEY);

/*
  This code will fetch all device information from your antares project.
  For more information visit https://antares.id/id/docs.html
*/

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
   Serial.println(antares.retrieveAllDevice(projectName));
   delay(10000);
}

 
