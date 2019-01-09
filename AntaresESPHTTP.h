#ifndef AntaresESPHTTP_H
#define AntaresESPHTTP_H
#include <Arduino.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

class Antares
{
    public:
      Antares(String accessKey);
      String createDevice(String projectName, String deviceName);
      String retrieveAllDevice(String projectName,int limit=0);
      String storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter);
      void begin(); // Initiate JSON buffer

      /*
        Overloaded functions start

        These functions are meant to push data into the
        initiated JSON buffer (created in
        the begin() function)
      */
      void push(String key, String value);
      void push(String key, int value);
      void push(String key, float value);
      void push(String key, double value);
      /* Overloaded functions end */

      void store(String projectName, String deviceName); // Store data in buffer to database
      void printPool(); // Print data to serial monitor
      void end();  // Clear JSON buffer
      String retrieveAllData(String projectName, String deviceName,int limit=0);
      JsonObject& retrieveLatestData(String projectName, String deviceName);
      bool wifiConnection(char* SSID, char* wifiPassword);
      bool checkWifiConnection();
      void setDebug(bool trueFalse);
      void setServer(String domain,String port);
      void setAntaresCse(String nameAntaresCse);
      void setAntaresId(String nameAntaresId);

    private:
      void printDebug(String text);
      String ipToString(IPAddress ip);
      String _accessKey;
      String _server = "http://platform.antares.id";
      String _port = "8080";
      String _antaresCse = "antares-cse";
      String _antaresId = "antares-id";
      char* _wifiSSID;
      char* _wifiPass;
      bool _debug=false;
      char* tempDebug;
      StaticJsonBuffer<10000> jsonBuffer;
      JsonObject& jsonPool = jsonBuffer.createObject();
      String jsonString;
};

#endif
