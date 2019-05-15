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

// 2-level nested json start

// Overloadded function: String
void AntaresESP8266HTTP::add(String key, String key2, String value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: int
void AntaresESP8266HTTP::add(String key, String key2, int value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: float
void AntaresESP8266HTTP::add(String key, String key2, float value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
}

// Overloadded function: double
void AntaresESP8266HTTP::add(String key, String key2, double value) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonString);
    if(_currentKey != key) {
        JsonObject& nested = object.createNestedObject(key);
        nested[key2] = value;
    }
    else {
        object[key][key2] = value;
    }
    String newInsert;
    object.printTo(newInsert);
    jsonString =  newInsert;
    _currentKey = key;
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
    WiFiClientSecure client;
    _getSuccess = false;
    jsonGetString = "";
    // Load root certificate in DER format into WiFiClientSecure object
    bool res = client.setCACert_P(caCert, caCertLen);

    if (!res) {
        printDebug("[ANTARES] Failed to load root CA certificate!\n");
        while (true) {
            yield();
        }
    }
    else {
        printDebug("[ANTARES] Loading root CA certificate success!\n");
    }

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portSecureNum)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    // Verify validity of server's certificate
    if (client.verifyCertChain(_serverNoHttp)) {
        printDebug("[ANTARES] Server certificate verified\n");
    } else {
        printDebug("[ANTARES] ERROR: certificate verification failed!\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName + "/la";
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& payloadJson = jsonBuffer.parseObject(line);
        String dataString = payloadJson["m2m:cin"]["con"];
        JsonObject& jsonGetPool = jsonBuffer.parseObject(dataString);
        jsonGetPool.printTo(jsonGetString);

        if(_debug) {
            jsonGetPool.prettyPrintTo(Serial);
            printDebug("\n");
        }
    }
    _getSuccess = true;
}

String AntaresESP8266HTTP::getRaw(String projectName, String deviceName) {
    WiFiClientSecure client;
    _getSuccess = false;
    jsonGetString = "";
    // Load root certificate in DER format into WiFiClientSecure object
    bool res = client.setCACert_P(caCert, caCertLen);

    if (!res) {
        printDebug("[ANTARES] Failed to load root CA certificate!\n");
        while (true) {
            yield();
        }
    }
    else {
        printDebug("[ANTARES] Loading root CA certificate success!\n");
    }

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portSecureNum)) {
        printDebug("[ANTARES] connection failed\n");
        return "Conn failed";
    }

    // Verify validity of server's certificate
    if (client.verifyCertChain(_serverNoHttp)) {
        printDebug("[ANTARES] Server certificate verified\n");
    } else {
        printDebug("[ANTARES] ERROR: certificate verification failed!\n");
        return "Cert error";
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName + "/la";
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return "Could not GET";
        }
    }

    String returnPayload = "";
    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& payloadJson = jsonBuffer.parseObject(line);
        String dataString = payloadJson["m2m:cin"]["con"];
        returnPayload = dataString;
    }
    _getSuccess = true;
    return returnPayload;
}

String AntaresESP8266HTTP::getRawNonSecure(String projectName, String deviceName) {
    WiFiClient client;
    _getSuccess = false;
    jsonGetString = "";

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portNum)) {
        printDebug("[ANTARES] connection failed\n");
        return "Conn failed";
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName + "/la";
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return "Could not GET";
        }
    }

    String returnPayload = "";
    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& payloadJson = jsonBuffer.parseObject(line);
        String dataString = payloadJson["m2m:cin"]["con"];
        returnPayload = dataString;
    }
    _getSuccess = true;
    return returnPayload;
}

void AntaresESP8266HTTP::getNonSecure(String projectName, String deviceName) {
    WiFiClient client;
    _getSuccess = false;
    jsonGetString = "";
    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect("platform.antares.id", 8080)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName + "/la";
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Accept: application/json\r\n" +
    //               "User-Agent: BuildFailureDetectorESP8266\r\n" +
               "Connection: close\r\n\r\n");

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = "";
        while(client.read() != '{');
        line += "{";
        line += client.readStringUntil('\r');
        DynamicJsonBuffer jsonBuffer;
        JsonObject& payloadJson = jsonBuffer.parseObject(line);
        String dataString = payloadJson["m2m:cin"]["con"];
        JsonObject& jsonGetPool = jsonBuffer.parseObject(dataString);
        jsonGetPool.printTo(jsonGetString);

        if(_debug) {
            jsonGetPool.prettyPrintTo(Serial);
            printDebug("\n");
        }
    }
    _getSuccess = true;
}

void AntaresESP8266HTTP::send(String projectName, String deviceName) {
    WiFiClientSecure client;
    // Load root certificate in DER format into WiFiClientSecure object
    bool res = client.setCACert_P(caCert, caCertLen);

    if (!res) {
        printDebug("[ANTARES] Failed to load root CA certificate!\n");
        while (true) {
            yield();
        }
    }
    else {
        printDebug("[ANTARES] Loading root CA certificate success!\n");
    }

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portSecureNum)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    // Verify validity of server's certificate
    if (client.verifyCertChain(_serverNoHttp)) {
        printDebug("[ANTARES] Server certificate verified\n");
    } else {
        printDebug("[ANTARES] ERROR: certificate verification failed!\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName;
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    jsonString.replace("\"", "\\\"");

    // Create JSON with Antares format
    String body;
    body += "{";
    body += "\"m2m:cin\":{";
    body += "\"con\":\"" + jsonString + "\"";
    body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = client.readStringUntil('\r');
        printDebug(line + "\n");
    }
    jsonString = "{}";
    _currentKey = "";
}

void AntaresESP8266HTTP::sendRaw(String text, String projectName, String deviceName) {
    WiFiClientSecure client;
    // Load root certificate in DER format into WiFiClientSecure object
    bool res = client.setCACert_P(caCert, caCertLen);

    if (!res) {
        printDebug("[ANTARES] Failed to load root CA certificate!\n");
        while (true) {
            yield();
        }
    }
    else {
        printDebug("[ANTARES] Loading root CA certificate success!\n");
    }

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portSecureNum)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    // Verify validity of server's certificate
    if (client.verifyCertChain(_serverNoHttp)) {
        printDebug("[ANTARES] Server certificate verified\n");
    } else {
        printDebug("[ANTARES] ERROR: certificate verification failed!\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName;
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    // Create JSON with Antares format
    String body;
    body += "{";
    body += "\"m2m:cin\":{";
    body += "\"con\":\"" + text + "\"";
    body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = client.readStringUntil('\r');
        printDebug(line + "\n");
    }
}

void AntaresESP8266HTTP::sendRawNonSecure(String text, String projectName, String deviceName) {
    WiFiClient client;

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portNum)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName;
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    // Create JSON with Antares format
    String body;
    body += "{";
    body += "\"m2m:cin\":{";
    body += "\"con\":\"" + text + "\"";
    body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = client.readStringUntil('\r');
        printDebug(line + "\n");
    }
}

void AntaresESP8266HTTP::sendNonSecure(String projectName, String deviceName) {
    WiFiClient client;

    // Connect to remote server
    printDebug("[ANTARES] connecting to " + String(_serverNoHttp) + "\n");
    if (!client.connect(_serverNoHttp, _portNum)) {
        printDebug("[ANTARES] connection failed\n");
        return;
    }

    String url = "/~/antares-cse/antares-id/"+ projectName +"/" + deviceName;
    printDebug("[ANTARES] requesting URL: " + url + "\n");

    jsonString.replace("\"", "\\\"");

    // Create JSON with Antares format
    String body;
    body += "{";
    body += "\"m2m:cin\":{";
    body += "\"con\":\"" + jsonString + "\"";
    body += "}";
    body += "}";

    const uint16_t bodyLength = body.length();

    client.print(String("POST ") + url + " HTTP/1.1\r\n" +
               "Host: " + _serverNoHttp + "\r\n" +
               "X-M2M-Origin: " + _accessKey + "\r\n" +
               "Accept: application/json\r\n" +
               "Connection: close\r\n" +
               "Content-Type: application/json;ty=4\r\n" +
               "Content-Length: " + String(bodyLength) + "\r\n\r\n" +
               body
           );

    Serial.println("[ANTARES] request sent\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            printDebug("[ANTARES] Client Timeout !\n");
            client.stop();
            return;
        }
    }

    while (client.connected()) {
        String line = client.readStringUntil('\r');
        printDebug(line + "\n");
    }
    jsonString = "{}";
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

String AntaresESP8266HTTP::getString(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    String value = object[key][key2];
    return value;
}

int AntaresESP8266HTTP::getInt(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key];
    return value;
}

int AntaresESP8266HTTP::getInt(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    int value = object[key][key2];
    return value;
}

float AntaresESP8266HTTP::getFloat(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key];
    return value;
}

float AntaresESP8266HTTP::getFloat(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    float value = object[key][key2];
    return value;
}

double AntaresESP8266HTTP::getDouble(String key) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key];
    return value;
}

double AntaresESP8266HTTP::getDouble(String key, String key2) {
    DynamicJsonBuffer jsonBuffer;
    JsonObject& object = jsonBuffer.parseObject(jsonGetString);
    double value = object[key][key2];
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

    // for (count=0;count<20;count++) {
    //     delay(500);
    //     printDebug(".");
    // }

    int counter = 0;
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        printDebug(".");
        counter++;
        if(counter >= 10) {
            counter = 0;
            printDebug("[ANTARES] Could not connect to " + SSID + "! Retrying...\n");
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[ANTARES] WiFi Connected!\n");
    printDebug("[ANTARES] IP Address: " + ipToString(WiFi.localIP()) + "\n");

    delay(1000);
    printDebug("[ANTARES] Setting time using SNTP\n");
    configTime(8 * 3600, 0, "pool.ntp.org", "time.nist.gov");
    time_t now = time(nullptr);

    while (now < 8 * 3600 * 2) {
        delay(500);
        Serial.print(".");
        now = time(nullptr);
    }
    printDebug("\n");
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);
    printDebug("Current time: ");
    printDebug(String(asctime(&timeinfo)));

    return true;
}

bool AntaresESP8266HTTP::wifiConnectionNonSecure(String SSID, String wifiPassword) {
    char ssidChar[sizeof(SSID)];
    char wifiPasswordChar[sizeof(SSID)];

    SSID.toCharArray(ssidChar, sizeof(SSID));
    wifiPassword.toCharArray(wifiPasswordChar, sizeof(wifiPassword));

    int count=0;
    _wifiSSID = ssidChar;
    _wifiPass = wifiPasswordChar;

    WiFi.begin(_wifiSSID, _wifiPass);
    printDebug("[ANTARES] Trying to connect to " + SSID + "...\n");

    // for (count=0;count<20;count++) {
    //     delay(500);
    //     printDebug(".");
    // }

    int counter = 0;
    while(WiFi.status() != WL_CONNECTED) {
        delay(500);
        printDebug(".");
        counter++;
        if(counter >= 10) {
            counter = 0;
            printDebug("[ANTARES] Could not connect to " + SSID + "! Retrying...\n");
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[ANTARES] WiFi Connected!\n");
    printDebug("[ANTARES] IP Address: " + ipToString(WiFi.localIP()) + "\n");
    return true;
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
