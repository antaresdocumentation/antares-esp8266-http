/*
  This code will deploy data to your Antares project device with the following structure:
  {
    "temperature": random-int,
    "humidity": random-int,
    "wind_speed": random-float,
    "rain_level": random-float,
    "latitude": "static-string",
    "longitude": "static-string",
  }
  For more information please visit https://antares.id/id/docs.html
*/

#include "AntaresESPHTTP.h"

#define ACCESSKEY "your-access-key"
#define WIFISSID "your-wifi-ssid"
#define PASSWORD "your-wifi-password"

String projectName = "your-project-name";
String deviceName = "your-device-name";

Antares antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD);
}

void loop() {
  // Variables
  int temp = random(25,30) ;
  int hum = random(75,90);
  float windsp = float(random(20, 30))/3.33;
  float rainlv = float(random(0, 20))/6.99;
  String lat = "-6.8718189";
  String lon = "107.5872477";

  // Add variable data to storage buffer
  antares.add("temperature", temp);
  antares.add("humidity", hum);
  antares.add("wind_speed", windsp);
  antares.add("rain_level", rainlv);
  antares.add("latitude", lat);
  antares.add("longitude", lon);

  // Send from buffer to Antares 
  antares.send(projectName, deviceName);
  delay(10000);
}
