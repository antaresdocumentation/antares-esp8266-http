#include "AntaresESPHTTP.h"

#define ACCESSKEY "e7e349fc2216941a:9d0cf82c25277bdd"
#define WIFISSID "IDC-HOTSPOT"
#define PASSWORD "telkomdds01"

String projectName = "SmartGarden";

Antares antares(ACCESSKEY);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
   Serial.println(antares.retrieveAllDevice(projectName));
   delay(10000);
}

 
