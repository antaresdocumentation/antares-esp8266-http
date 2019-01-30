#include "AntaresESP8266HTTP.h"

AntaresESP8266HTTP::AntaresESP8266HTTP(String accessKey) {
    _accessKey = accessKey;
}

String AntaresESP8266HTTP::createDevice(String projectName, String deviceName){
    HTTPClient http;
    WiFiClient client;
	printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");
	http.begin(_server+":" + _port+ "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName); //HTTP
    http.addHeader("Content-Type", "application/json;ty=3");
    http.addHeader("X-M2M-Origin", _accessKey);
	String body="{\"m2m:cnt\": {\"rn\": \""+deviceName+"\"}}";
	printDebug("[ANTARES] POST...\n");
	printDebug("[ANTARES] " + body +"\n");
	int httpCode = http.POST(body);

    if(httpCode > 0) {
       printDebug("[ANTARES] POST... code: "+(String)httpCode+"\n");

       if(httpCode == 201) {
           String payload = http.getString();
           printDebug("[ANTARES] " + payload +"\n");
           printDebug("[ANTARES] Created\n");
       }
       else if(httpCode == 409) {
           printDebug("[ANTARES] Conflict\n");
       }
       else {
           printDebug("[ANTARES] Error\n");
       }
   }
   else {
       printDebug("[ANTARES] POST... failed, error: "+(String)http.errorToString(httpCode).c_str()+"\n");
   }
   http.end();
   return (String)httpCode;
}

String AntaresESP8266HTTP::retrieveAllDevice(String projectName,int limit){
	HTTPClient http;
    WiFiClient client;

    DynamicJsonBuffer jsonBuffer;
	printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");
    String Limit="";

    if (limit!=0) Limit = "&lim="+(String)limit;

    http.begin(_server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"?fu=1&ty=3"+Limit); //HTTP
	http.addHeader("Content-Type", "application/json;ty=3");
	http.addHeader("X-M2M-Origin", _accessKey);
	printDebug("[ANTARES] GET...\n");
	int httpCode = http.GET();
	if(httpCode > 0) {
        printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            printDebug(payload);
            JsonObject& payloadJson = jsonBuffer.parseObject(payload);
            payload = payloadJson["m2m:uril"].as<String>();
            payload.replace("/antares-cse/antares-id/"+projectName+"/","");
            payload.replace(" ",",");
            printDebug(payload+"\n");
            return payload;
		}
    }
    else {
		printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
	}

    http.end();
    return "[ANTARES] Error";
}

void AntaresESP8266HTTP::send(String projectName, String deviceName) {
    HTTPClient http;
    WiFiClient client;

    String Uri = _server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName;
  	printDebug("\n[ANTARES] CONNECT TO "+Uri+"...\n");
    http.begin(Uri);
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("Accept", "application/json");
    http.addHeader("X-M2M-Origin", _accessKey);

    printDebug("[ANTARES] POST...\n");

    if(_debug) {
        DynamicJsonBuffer jsonBuffer;
        JsonObject& object = jsonBuffer.parseObject(jsonString);
        object.prettyPrintTo(Serial);
        Serial.println();
    }

    jsonString.replace("\"", "\\\"");

    String body;
    body += "{";
    body += "\"m2m:cin\": {";
    body += "\"con\": \"" + jsonString + "\"";
    body += "}";
    body += "}";
    // body += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>";
    // body += jsonString;
    // body += "</con></m2m:cin>\n";

    int httpCode = http.POST(body);
  	if(httpCode > 0) {
  		printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
  		if(httpCode == HTTP_CODE_OK) {
  			String payload = http.getString();
  			printDebug(payload);
  		}
  	} else {
  		printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
  	}

    jsonString = "{}"; // Empty the json string
  	http.end();
}

// Overloadded function: String
void AntaresESP8266HTTP::add(String key, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: int
void AntaresESP8266HTTP::add(String key, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: float
void AntaresESP8266HTTP::add(String key, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

// Overloadded function: double
void AntaresESP8266HTTP::add(String key, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    object[key] = value;
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
}

void AntaresESP8266HTTP::printData() {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& sendObject = jsonBuffer.parseObject(jsonString);
    JsonObject& getObject = jsonBuffer.parseObject(jsonGetString);
    printDebug("\n\n[ANTARES] Data to send: \n\n");
    sendObject.prettyPrintTo(Serial);
    printDebug("\n\n[ANTARES] Data available to get: \n\n");
    getObject.prettyPrintTo(Serial);
}

void AntaresESP8266HTTP::get(String projectName, String deviceName) {
    HTTPClient http;
    WiFiClient client;

    _getSuccess = false;
    jsonGetString = "";
    DynamicJsonBuffer jsonBufferTest;

    printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");

    http.begin(_server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName+"/la"); //HTTP
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("X-M2M-Origin", _accessKey);
    printDebug("[ANTARES] GET...\n");
    int httpCode = http.GET();
    if(httpCode > 0) {
        printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
        if(httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            JsonObject& payloadJson = jsonBufferTest.parseObject(payload);
            String dataString = payloadJson["m2m:cin"]["con"];
            JsonObject& jsonGetPool = jsonBufferTest.parseObject(dataString);
            jsonGetPool.printTo(jsonGetString);

            if(_debug) {
                Serial.println("\n[ANTARES] JSON GET:\n");
                jsonGetPool.printTo(Serial);
                Serial.println("\n");
            }
            _getSuccess = true;
        }
    } else {
        printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
    }
    http.end();
    // return "[ANTARES] Error";
}

bool AntaresESP8266HTTP::getSuccess() {
    return _getSuccess;
}

void AntaresESP8266HTTP::getLatestTest(String projectName, String deviceName) {
    WiFiClient client;

    printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");

    if(client.connect(_server, _portNum)) {
        printDebug("[ANTARES] connected!");
        client.stop();
    }
    else {
        printDebug("[ANTARES] connection failed!");
        client.stop();
    }
}

String AntaresESP8266HTTP::getString(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key];
    return value;
}

int AntaresESP8266HTTP::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    return value;
}

float AntaresESP8266HTTP::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    return value;
}

double AntaresESP8266HTTP::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    return value;
}

String AntaresESP8266HTTP::storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter){
    HTTPClient http;
    WiFiClient client;
    String Uri = _server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName;
	printDebug("\n[ANTARES] CONNECT TO "+Uri+"...\n");
    http.begin(Uri); //HTTP
    http.addHeader("Content-Type", "application/xml;ty=4");
    http.addHeader("X-M2M-Origin", _accessKey);
    String body="<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>{";

    for (int i=0; i<sizeParameter; i++) {
        body += "\""+nameData[i]+"\":\""+valueData[i]+"\"";

        if (i != (sizeParameter-1))
        body += ",";
    }

    body += "}</con></m2m:cin>\n";

    printDebug("[ANTARES] POST...\n");
    printDebug("[ANTARES] " + body +"\n");
	int httpCode = http.POST(body);
	if(httpCode > 0) {
		printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
		if(httpCode == HTTP_CODE_OK) {
			String payload = http.getString();
			printDebug(payload);
		}
	} else {
		printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
	}

	http.end();
    return (String)httpCode;
}

String AntaresESP8266HTTP::retrieveAllData(String projectName, String deviceName,int limit){
  HTTPClient http;
  WiFiClient client;

  DynamicJsonBuffer jsonBuffer;

  printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");
  String Limit="";
  if (limit!=0) Limit = "&lim="+(String)limit;
  http.begin(_server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName+"?fu=1&ty=4"+Limit); //HTTP
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-M2M-Origin", _accessKey);
  printDebug("[ANTARES] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) {
      printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          printDebug(payload);
          JsonObject& payloadJson = jsonBuffer.parseObject(payload);
          payload = payloadJson["m2m:uril"].as<String>();
          payload.replace("/antares-cse/antares-id/"+projectName+"/"+deviceName+"/","");
          payload.replace(" ",",");
          printDebug(payload+"\n");
          return payload;
      }
  } else {
      printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
  }

  http.end();
  return "[ANTARES] Error";
}

String AntaresESP8266HTTP::retrieveLatestData(String projectName, String deviceName){
  HTTPClient http;
  WiFiClient client;

  printDebug("\n[ANTARES] CONNECT TO "+_server+"...\n");

  http.begin(_server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName+"/la"); //HTTP
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-M2M-Origin", _accessKey);
  printDebug("[ANTARES] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) {
      printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          return payload;
      }
  } else {
      printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
  }

  http.end();
  // return "[ANTARES] Error";
}

bool AntaresESP8266HTTP::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count=0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[ANTARES] Trying to connect to " + SSID + "...\n");

    for (count=0;count<20;count++) {
        delay(500);
        printDebug(".");
    }

    if (WiFi.status() != WL_CONNECTED) {
        printDebug("[ANTARES] Could not connect to " + SSID + ".\n");
        return false;
    }
    else {
        WiFi.setAutoReconnect(true);
        printDebug("\n[ANTARES] WiFi Connected!\n");
        printDebug("[ANTARES] IP Address: " + ipToString(WiFi.localIP()) + "\n");
        return true;
    }
}

bool AntaresESP8266HTTP::checkWifiConnection() {
    if(WiFi.status() != WL_CONNECTED) {
        printDebug("[ANTARES] WIFI RECONNECT...");
        return wifiConnection(_wifiSSID, _wifiPass);
    }
}

void AntaresESP8266HTTP::setDebug(bool trueFalse){
    _debug = trueFalse;
}

void AntaresESP8266HTTP::setServer(String domain, String port){
    _server = domain;
    _port = port;
}

void AntaresESP8266HTTP::setAntaresCse(String nameAntaresCse){
    _antaresCse = nameAntaresCse;
}

void AntaresESP8266HTTP::setAntaresId(String nameAntaresId){
    _antaresId = nameAntaresId;
}

void AntaresESP8266HTTP::printDebug(String text){
    if (_debug)
        Serial.print(text);
}

String AntaresESP8266HTTP::ipToString(IPAddress ip){
    String s="";
    for (int i=0; i<4; i++)
        s += i  ? "." + String(ip[i]) : String(ip[i]);
    return s;
}
