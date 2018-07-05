#include "AntaresESPHTTP.h"

#define SERVER "http://platform.antares.id"
#define PORT "8080"
#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";
String deviceName = "your-device-name";

Antares antares(ACCESSKEY,SERVER,PORT);

void setup() {
    Serial.begin(115200);
    antares.setDebug(true);
    antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
   int sizeData = 2; 
   String dataName[sizeData],dataValue[sizeData];
   dataName[0]= "Temperature";
   dataName[1]= "Humidity";

   dataValue[0]= (String)random(50,100);
   dataValue[1]= (String)random(50,100);
   Serial.println(antares.storeData(projectName, deviceName, dataName, dataValue,sizeData));
   delay(10000);
   
}

 
