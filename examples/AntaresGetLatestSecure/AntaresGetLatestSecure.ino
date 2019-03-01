/*
  This code will fetch the latest data from your antares project device.
  Your Antares project device must have a structure like this:
  (Note that nesting the JSON object can only be done up to 2 levels using this library)
  {
    "temperature": some-integer,
    "humidity": some-integer,
    "wind_speed": some-float,
    "rain_level": some-float,
    "location" : {
      "latitude": "static-string",
      "longitude": "static-string"
    }
  }
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
}

void loop() {
  // Store latest value in buffer
  antares.getSecure(projectName, deviceName);

  // Check if we're actually getting data
  if(antares.getSuccess()) {
    // Get each values
    int temp = antares.getInt("temperature");
    int hum = antares.getInt("humidity");
    float windsp = antares.getFloat("wind_speed");
    float rainlv = antares.getFloat("rain_level");
    String lat = antares.getString("location", "latitude");
    String lon = antares.getString("location", "longitude");

    // Print each values
    Serial.println("Temperature: " + String(temp));
    Serial.println("Humidity: " + String(hum));
    Serial.println("Wind speed: " + String(windsp));
    Serial.println("Rain level: " + String(rainlv));
    Serial.println("Latitude: " + lat);
    Serial.println("Longitude: " + lon);
  }
  delay(10000);
}
