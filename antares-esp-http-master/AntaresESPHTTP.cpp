#include "AntaresESPHTTP.h"

Antares::Antares(String accessKey) {
    _accessKey = accessKey;
}

String Antares::createDevice(String projectName, String deviceName){
	HTTPClient http;
	printDebug("\n[ANTARES] CONNECT TO "+(String)SERVER+"...\n");
	http.begin((String)SERVER+":" + (String)PORT + "/~/antares-cse/antares-id/"+projectName); //HTTP
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
	printDebug("\n[ANTARES] CONNECT TO "+(String)SERVER+"...\n");
  String Limit="";
  if (limit!=0) Limit = "&lim="+(String)limit;
	http.begin((String)SERVER+":" + (String)PORT + "/~/antares-cse/antares-id/"+projectName+"?fu=1&ty=3"+Limit); //HTTP
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

String Antares::storeData(String projectName, String deviceName, String nameData[], String valueData[], int sizeParameter){
	HTTPClient http;
  String Uri = (String)SERVER+":" + (String)PORT + "/~/antares-cse/antares-id/"+projectName+"/"+deviceName;
	printDebug("\n[ANTARES] CONNECT TO "+Uri+"...\n");
  http.begin(Uri); //HTTP
  http.addHeader("Content-Type", "application/xml;ty=4");
  http.addHeader("X-M2M-Origin", _accessKey);
  String body="<m2m:cin xmlns:m2m=\"http://www.onem2m.org/xml/protocols\"><cnf>message</cnf><con>&lt;obj&gt;";
  for (int i=0; i<sizeParameter; i++)
    body += "&lt;int name=\""+nameData[i]+"\" val=\""+valueData[i]+"\"/&gt;";
  body += "&lt;/obj&gt;</con></m2m:cin>\n";

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
  printDebug("\n[ANTARES] CONNECT TO "+(String)SERVER+"...\n");
  String Limit="";
  if (limit!=0) Limit = "&lim="+(String)limit;
  http.begin((String)SERVER+":" + (String)PORT + "/~/antares-cse/antares-id/"+projectName+"/"+deviceName+"?fu=1&ty=4"+Limit); //HTTP
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
  printDebug("\n[ANTARES] CONNECT TO "+(String)SERVER+"...\n");

  http.begin((String)SERVER+":" + (String)PORT + "/~/antares-cse/antares-id/"+projectName+"/"+deviceName+"/la"); //HTTP
  http.addHeader("Content-Type", "application/json");
  http.addHeader("X-M2M-Origin", _accessKey);
  printDebug("[ANTARES] GET...\n");
  int httpCode = http.GET();
  if(httpCode > 0) {
      printDebug("[ANTARES] RESPONSE CODE : " +(String) httpCode+"\n");
      if(httpCode == HTTP_CODE_OK) {
          String payload = http.getString();
          printDebug(payload);
          return payload;
      }
  } else {
      printDebug("[ANTARES] GET... failed, error: " + (String) http.errorToString(httpCode).c_str() + "\n");
  }
  http.end();
  return "[ANTARES] Error";
}

bool Antares::wifiConnection(char* ssid, char* pass) {
    int count=0;
    WiFi.begin(ssid, pass);
    printDebug("\n[ANTARES] WIFI CONNECTING");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        printDebug(".");
        count++;
        if (count>=20)
        {
          printDebug("[ANTARES] Cannot Connect " + (String) ssid);
          ESP.reset();
        }
    }

    WiFi.setAutoReconnect(true);
    printDebug("\n[ANTARES] WIFI CONNECTED\n");
    printDebug("[ANTARES] IP ADDRESS: ");
    printDebug(ipToString(WiFi.localIP()));
    printDebug("\n");
    return true;
}

void Antares::setDebug(bool trueFalse){
  _debug = trueFalse;
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
