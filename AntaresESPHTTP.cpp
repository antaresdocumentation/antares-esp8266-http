#include "AntaresESPHTTP.h"

Antares::Antares(String accessKey) {
    _accessKey = accessKey;
}

String Antares::createDevice(String projectName, String deviceName){
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
      else if (httpCode == 409){
        printDebug("[ANTARES] Conflict\n");
      }
      else
      {
        printDebug("[ANTARES] Error\n");
      }
	}
	else {
			printDebug("[ANTARES] POST... failed, error: "+(String)http.errorToString(httpCode).c_str()+"\n");
	}

	http.end();
  return (String)httpCode;
}

String Antares::retrieveAllDevice(String projectName,int limit){
	HTTPClient http;
    WiFiClient client;

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
	} else {
			printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
	}
	http.end();
  return "[ANTARES] Error";
}

void Antares::send(String projectName, String deviceName) {
    jsonPool.printTo(jsonString); // Convert json object into string

    printDebug("\n[ANTARES] ");
    printDebug(jsonString);
    printDebug("\n");

    HTTPClient http;
    WiFiClient client;

    String Uri = _server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName;
  	printDebug("\n[ANTARES] CONNECT TO "+Uri+"...\n");
    http.begin(Uri);
    http.addHeader("Content-Type", "application/xml;ty=4");
    http.addHeader("X-M2M-Origin", _accessKey);
    String body;
    body += "<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>";
    body += jsonString;
    body += "</con></m2m:cin>\n";

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
    jsonString = ""; // Empty the json string
    jsonBuffer.clear();
    JsonObject& jsonPool = jsonBuffer.createObject();
  	http.end();
}

void Antares::begin() {
    JsonObject& jsonPool = jsonBuffer.createObject();
}

// Overloadded function: String
void Antares::add(String key, String value) {
    jsonPool[key] = value;
}

// Overloadded function: int
void Antares::add(String key, int value) {
    jsonPool[key] = value;
}

// Overloadded function: float
void Antares::add(String key, float value) {
    jsonPool[key] = value;
}

// Overloadded function: double
void Antares::add(String key, double value) {
    jsonPool[key] = value;
}

void Antares::printPool() {
    jsonPool.printTo(jsonString);
    Serial.println(jsonString);
    // jsonBuffer.clear();
    jsonString = "";
}

void Antares::get(String projectName, String deviceName) {
    HTTPClient http;
    WiFiClient client;


    jsonGetString = "";

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
            JsonObject& payloadJson = jsonGetBuffer.parseObject(payload);
            jsonGetBuffer.clear();
            String dataString = payloadJson["m2m:cin"]["con"];
            JsonObject& jsonGetPool = jsonGetBuffer.parseObject(dataString);
            jsonGetPool.printTo(jsonGetString);
            jsonGetBuffer.clear();
            Serial.println(jsonGetString);
        }
    } else {
        printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
    }
    http.end();
    // return "[ANTARES] Error";
}

void Antares::getTest(String projectName, String deviceName) {
    WiFiClient client;

    if(!client.connect(_serverNoHttp, _portNum)) {
        printDebug("[ANTARES] Connection failed!\n");
    }
    else {
        printDebug("[ANTARES] Connection successful!\n");
        String url = "/~/" + _antaresCse + "/" + _antaresId + "/" + projectName + "/" + deviceName + "/" + "la";
        printDebug("[ANTARES] Fetching data from" + url + "\n");

        String request = (String("GET ") + url + " HTTP/1.1\r\n" +
                     "Host: " + _serverNoHttp + ":8080\r\n" +
                     "Content-Type: application/json;ty=4\r\n" +
                     "X-M2M-Origin: " + _accessKey + "\r\n" +
                     "Accept: application/json" + "\r\n" +
                     "Connection: close\r\n\r\n"
                 );
        printDebug(request);
        client.print(request);
        unsigned long timeout = millis();
        while(client.available() == 0) {
            if(millis() - timeout > 5000) {
                printDebug("[ANTARES] Timeout!");
                client.stop();
                return;
            }
        }

        while(client.available()) {
            if(client.read() == '{') {
                String payload = "{";
                payload += client.readStringUntil('\r');
                JsonObject& payloadJson = jsonGetBuffer.parseObject(payload);
                String jsonGetString = payloadJson["m2m:cin"]["con"];
                jsonGetBuffer.clear();
                Serial.println(jsonGetString);
                // String dataString = payloadJson["m2m:cin"]["con"];
                // JsonObject& jsonGetPool = jsonGetBuffer.parseObject(dataString);
                // jsonGetPool.printTo(jsonGetString);
                // jsonBuffer.clear();
                // Serial.println(jsonGetString);
                // printDebug(line);
                client.stop();
                client.flush();
            }
        }

        printDebug("\n[ANTARES] Closing connection...");
    }
}

void Antares::getLatestTest(String projectName, String deviceName) {
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

String Antares::getString(String key) {
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key];
    jsonBuffer.clear();
    return value;
}

int Antares::getInt(String key) {
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    jsonBuffer.clear();
    return value;
}

float Antares::getFloat(String key) {
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    jsonBuffer.clear();
    return value;
}

double Antares::getDouble(String key) {
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    jsonBuffer.clear();
    return value;
}

String Antares::storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter){
	HTTPClient http;
    WiFiClient client;
  String Uri = _server+":" + _port + "/~/"+_antaresCse+"/"+_antaresId+"/"+projectName+"/"+deviceName;
	printDebug("\n[ANTARES] CONNECT TO "+Uri+"...\n");
  http.begin(Uri); //HTTP
  http.addHeader("Content-Type", "application/xml;ty=4");
  http.addHeader("X-M2M-Origin", _accessKey);
  String body="<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>{";
  for (int i=0; i<sizeParameter; i++)
  {
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

String Antares::retrieveAllData(String projectName, String deviceName,int limit){
  HTTPClient http;
  WiFiClient client;

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

String Antares::retrieveLatestData(String projectName, String deviceName){
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

bool Antares::wifiConnection(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count=0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("\n[ANTARES] WIFI CONNECTING");

    for (count=0;count<20;count++)
    {
      delay(500);
      printDebug(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
      printDebug("[ANTARES] Cannot Connect " + (String) _wifiSSID);
      return false;
    }
    else
    {
      WiFi.setAutoReconnect(true);
      printDebug("\n[ANTARES] WIFI CONNECTED\n");
      printDebug("[ANTARES] IP ADDRESS: ");
      printDebug(ipToString(WiFi.localIP()));
      printDebug("\n");
      return true;
    }

}

bool Antares::checkWifiConnection()
{
  if (WiFi.status() != WL_CONNECTED) {
    printDebug("[ANTARES] WIFI RECONNECT...");
    return wifiConnection(_wifiSSID, _wifiPass);
  }
}

void Antares::setDebug(bool trueFalse){
  _debug = trueFalse;
}

void Antares::setServer(String domain, String port){
  _server = domain;
  _port = port;
}

void Antares::setAntaresCse(String nameAntaresCse){
  _antaresCse = nameAntaresCse;
}

void Antares::setAntaresId(String nameAntaresId){
  _antaresId = nameAntaresId;
}

void Antares::printDebug(String text){
  if (_debug)
    Serial.print(text);
}

String Antares::ipToString(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++)
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  return s;
}

void Antares::measureSize() {
    size_t len = jsonPool.measureLength();
    size_t size = len + 1;

    Serial.print("Pool size: ");
    Serial.println(size);

    Serial.print("Buffer size: ");
    Serial.println(jsonBuffer.size());
}

void Antares::measureGetSize() {
    Serial.print("Buffer size: ");
    Serial.println(jsonBuffer.size());
}
