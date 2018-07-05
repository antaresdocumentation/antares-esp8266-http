#ifndef AntaresESPHTTP_H
#define AntaresESPHTTP_H
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#define SERVER "http://platform.antares.id"
#define PORT "8080"

class Antares
{
    public:
      Antares(String accessKey,String server, String port);
      // Antares(String accessKey);
      String createDevice(String projectName, String deviceName);
      String retrieveAllDevice(String projectName,int limit=0);
      String storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter);
      String retrieveAllData(String projectName, String deviceName,int limit=0);
      String retrieveLatestData(String projectName, String deviceName);
      bool wifiConnection(char* SSID, char* wifiPassword);
      bool checkWifiConnection();
      void setDebug(bool trueFalse);

    private:
      void printDebug(String text);
      String ipToString(IPAddress ip);
      String _accessKey;
      String _server = SERVER;
      String _port = PORT;
      char* _wifiSSID;
      char* _wifiPass;
      bool _debug=false;
      char* tempDebug;
      StaticJsonBuffer<10000> jsonBuffer;
};

#endif
