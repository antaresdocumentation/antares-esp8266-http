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

#define ACCESSKEY "b4e89ce2436b9d90:202c7b14b849c084"
#define WIFISSID "LAB IOT 3"
#define PASSWORD "labiot2018"

#define projectName "weather-station"
#define deviceName "station1"

AntaresESP8266HTTP antares(ACCESSKEY);

void setup() {
  Serial.begin(115200);
  antares.setDebug(true);
  antares.wifiConnection(WIFISSID,PASSWORD)
  /* Use wifiConnectionNonSecure instead if you don't want to use HTTPS
   * and avoid SNTP matching */
  //antares.wifiConnectionNonSecure(WIFISSID,PASSWORD);
}

void loop() {
  antares.get(projectName, deviceName); // Store latest value in buffer
  /*
    Uncomment the line below to use HTTP instead of HTTPS.
    Will be faster, but less secure
  */
  // antares.getNonSecure(projectName, deviceName);

 //  Check if we're actually getting data
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
