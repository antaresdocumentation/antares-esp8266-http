#ifndef AntaresESPHTTP_H
#define AntaresESPHTTP_H
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define SERVER "http://platform.antares.id"
#define PORT 8080

class Antares
{
    public:
      Antares(String accessKey);
      String createDevice(String projectName, String deviceName);
      String retrieveAllDevice(String projectName,int limit=0);
      String storeData(String projectName, String deviceName, String value, String unit);
      String retrieveAllData(String projectName, String deviceName,int limit=0);
      String retrieveLatestData(String projectName, String deviceName);
      bool wifiConnection(char *ssid, char *pass);
      void setDebug(bool trueFalse);
      
    private:
      void printDebug(String text);
      String ipToString(IPAddress ip);
      String _accessKey;
      bool _debug=false;
      char* tempDebug;
      StaticJsonBuffer<10000> jsonBuffer;
};

#endif
