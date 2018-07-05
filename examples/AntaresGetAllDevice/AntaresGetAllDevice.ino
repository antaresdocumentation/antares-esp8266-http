#include "AntaresESPHTTP.h"

#define SERVER "http://platform.antares.id"
#define PORT "8080"
#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";

Antares antares(ACCESSKEY,SERVER,PORT);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
   Serial.println(antares.retrieveAllDevice(projectName));
   delay(10000);
}

 
