#include "YeelinkHTTPArduino.h"

static String LF = "\x0A";
static String API_HOST = "api.yeelink.net";

static String headerGet = "Host: " + API_HOST + LF
 + "Pragma: no-cache" + LF
 + "Connection: keep-alive"; 

static String headerPost = "Host: " + API_HOST + LF
 + "Content-Type: application/json; charset=utf-8" + LF 
 + "Connection: keep-alive";  

Sensor::Sensor(String APIKey, String deviceID, String sensorID)
{
  _APIKey = APIKey;
  _deviceID = deviceID;
  _sensorID = sensorID;
}

void Sensor::request()
{
  _FSON.initStreamScanner();

  String requestLine = "GET /v1.0/device/" + _deviceID + "/sensor/" 
                       + _sensorID + "/datapoints HTTP/1.1";  

  Serial.println(requestLine);  
  Serial.println(headerGet);
  Serial.println("U-APiKey: " + _APIKey);
  Serial.println("");  
}

bool Sensor::available()
{
  while (Serial.available()) {
    char c = Serial.read();    
    bool found = _FSON.setStreamedObject(c);
    if (found) {
      return found;
    }
  } 
  
  return false;
}

String Sensor::get()
{
  String result = _FSON.getProperty("value");
  
  /* Avoid FSON bug. With the following, FSON will return "1}"
  
     {"timestamp":"2013-08-16T13:39:13","value":1} 
   */   
  if (result.endsWith("}")) 
    return result.substring(0, result.length() - 1);
  else
    return result;
}

String Sensor::get(String propertyName)
{  
  String result = _FSON.getProperty(propertyName);
  
  /* Avoid FSON bug. With the following, FSON will return "1}"
  
     {"timestamp":"2013-08-16T13:39:13","value":1} 
   */   
  if (result.endsWith("}")) 
    return result.substring(0, result.length() - 1);
  else
    return result;
}

void Sensor::update(String value)
{
  _FSON.initStreamScanner();
  String body = "{ \"value\": " + value + " }";  

  String requestLine = "POST /v1.0/device/" + _deviceID + "/sensor/" + _sensorID 
                     + "/datapoints HTTP/1.1";

  Serial.println(requestLine);
  Serial.println(headerPost);
  Serial.println("U-APiKey: " + _APIKey);
  Serial.print("Content-Length: "); Serial.println(body.length());
  Serial.println("");
  Serial.println(body);  
}