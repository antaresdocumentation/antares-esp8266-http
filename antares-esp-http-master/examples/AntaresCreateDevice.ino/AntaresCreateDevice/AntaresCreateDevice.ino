#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";

Antares antares(ACCESSKEY);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
   Serial.println(antares.createDevice(projectName,"test3"));
   //Serial.println(retrieveAllDevice(projectName));
   //Serial.println(antares.storeData(projectName, "test1", (String)random(50,100), "Celcius"));
   //Serial.println(antares.retrieveAllData(projectName, deviceName));
   //Serial.println(antares.retrieveLatestData(projectName, deviceName));
   delay(10000);
}

 
