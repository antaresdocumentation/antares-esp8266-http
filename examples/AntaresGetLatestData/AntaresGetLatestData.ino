/*
  This code will fetch the latest data from your antares project device.
<<<<<<< HEAD
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
=======
  For more information visit https://antares.id/id/docs.html
>>>>>>> fb45a030c8547cde204b3b9d260750a9dcfec159
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
<<<<<<< HEAD
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
=======
  Serial.println(antares.retrieveLatestData(projectName, deviceName));
>>>>>>> fb45a030c8547cde204b3b9d260750a9dcfec159
  delay(10000);
}
