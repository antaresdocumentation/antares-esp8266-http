/*
  This code will fetch the latest data from your antares project device.
  Your Antares project device must have a structure like this:
  {
    "temperature": some-integer,
    "humidity": some-integer,
    "wind_speed": some-float,
    "rain_level": some-float,
    "latitude": "some-string",
    "longitude": "some-string"
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
  // Store latest value in buffer
  antares.get(projectName, deviceName);
  
  // Get each values
  int temp = antares.getInt("temperature");
  int hum = antares.getInt("humidity");
  float windsp = antares.getFloat("wind_speed");
  float rainlv = antares.getFloat("rain_level");
  String lat = antares.getString("latitude");
  String lon = antares.getString("longitude");

  // Print each values
  Serial.println("Temperature: " + String(temp));
  Serial.println("Humidity: " + String(hum));
  Serial.println("Wind speed: " + String(windsp));
  Serial.println("Rain level: " + String(rainlv));
  Serial.println("Latitude: " + lat);
  Serial.println("Longitude: " + lon);
  delay(10000);
}
